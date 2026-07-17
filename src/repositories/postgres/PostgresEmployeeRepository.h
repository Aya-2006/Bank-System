#pragma once
#include "../interfaces/IEmployeeRepository.h"
#include <libpq-fe.h>
#include <stdexcept>
#include <string>
using namespace std;

class PostgresEmployeeRepository : public IEmployeeRepository {
private:
    PGconn* conn;

    static Employee rowToEmployee(PGresult* res, int row) {
        return Employee(
            stoi(PQgetvalue(res, row, 0)),
            PQgetvalue(res, row, 1),
            PQgetvalue(res, row, 2),
            stod(PQgetvalue(res, row, 3))
        );
    }

public:
    explicit PostgresEmployeeRepository(PGconn* dbConn) : conn(dbConn) {}

    int add(Employee& employee) override {
        const char* sql = "INSERT INTO Employees (name, password, salary) VALUES ($1, $2, $3) RETURNING id;";
        string salaryStr = to_string(employee.getSalary());
        const char* params[3] = { employee.getName().c_str(), employee.getPassword().c_str(), salaryStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 3, nullptr, params, nullptr, nullptr, 0);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            string err = PQresultErrorMessage(res);
            PQclear(res);
            throw runtime_error("Failed to insert employee: " + err);
        }
        int newId = stoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        employee.setId(newId);
        return newId;
    }

    bool update(const Employee& employee) override {
        const char* sql = "UPDATE Employees SET name=$1, password=$2, salary=$3 WHERE id=$4;";
        string salaryStr = to_string(employee.getSalary());
        string idStr = to_string(employee.getId());
        const char* params[4] = { employee.getName().c_str(), employee.getPassword().c_str(),
                                   salaryStr.c_str(), idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 4, nullptr, params, nullptr, nullptr, 0);
        bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
        string affected = ok ? PQcmdTuples(res) : "0";
        PQclear(res);
        return ok && affected != "0" && !affected.empty();
    }

    optional<Employee> findById(int id) override {
        const char* sql = "SELECT id, name, password, salary FROM Employees WHERE id=$1;";
        string idStr = to_string(id);
        const char* params[1] = { idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 1, nullptr, params, nullptr, nullptr, 0);
        optional<Employee> result;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            result = rowToEmployee(res, 0);
        }
        PQclear(res);
        return result;
    }

    vector<Employee> getAll() override {
        const char* sql = "SELECT id, name, password, salary FROM Employees;";
        PGresult* res = PQexec(conn, sql);

        vector<Employee> results;
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            for (int i = 0; i < PQntuples(res); i++) {
                results.push_back(rowToEmployee(res, i));
            }
        }
        PQclear(res);
        return results;
    }
};
