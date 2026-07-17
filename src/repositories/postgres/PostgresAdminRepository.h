#pragma once
#include "../interfaces/IAdminRepository.h"
#include <libpq-fe.h>
#include <stdexcept>
#include <string>
using namespace std;

class PostgresAdminRepository : public IAdminRepository {
private:
    PGconn* conn;

    static Admin rowToAdmin(PGresult* res, int row) {
        return Admin(
            stoi(PQgetvalue(res, row, 0)),
            PQgetvalue(res, row, 1),
            PQgetvalue(res, row, 2),
            stod(PQgetvalue(res, row, 3))
        );
    }

public:
    explicit PostgresAdminRepository(PGconn* dbConn) : conn(dbConn) {}

    int add(Admin& admin) override {
        const char* sql = "INSERT INTO Admins (name, password, salary) VALUES ($1, $2, $3) RETURNING id;";
        string salaryStr = to_string(admin.getSalary());
        const char* params[3] = { admin.getName().c_str(), admin.getPassword().c_str(), salaryStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 3, nullptr, params, nullptr, nullptr, 0);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            string err = PQresultErrorMessage(res);
            PQclear(res);
            throw runtime_error("Failed to insert admin: " + err);
        }
        int newId = stoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        admin.setId(newId);
        return newId;
    }

    bool update(const Admin& admin) override {
        const char* sql = "UPDATE Admins SET name=$1, password=$2, salary=$3 WHERE id=$4;";
        string salaryStr = to_string(admin.getSalary());
        string idStr = to_string(admin.getId());
        const char* params[4] = { admin.getName().c_str(), admin.getPassword().c_str(),
                                   salaryStr.c_str(), idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 4, nullptr, params, nullptr, nullptr, 0);
        bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
        string affected = ok ? PQcmdTuples(res) : "0";
        PQclear(res);
        return ok && affected != "0" && !affected.empty();
    }

    optional<Admin> findById(int id) override {
        const char* sql = "SELECT id, name, password, salary FROM Admins WHERE id=$1;";
        string idStr = to_string(id);
        const char* params[1] = { idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 1, nullptr, params, nullptr, nullptr, 0);
        optional<Admin> result;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            result = rowToAdmin(res, 0);
        }
        PQclear(res);
        return result;
    }

    vector<Admin> getAll() override {
        const char* sql = "SELECT id, name, password, salary FROM Admins;";
        PGresult* res = PQexec(conn, sql);

        vector<Admin> results;
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            for (int i = 0; i < PQntuples(res); i++) {
                results.push_back(rowToAdmin(res, i));
            }
        }
        PQclear(res);
        return results;
    }
};
