#pragma once
#include "../interfaces/IClientRepository.h"
#include <libpq-fe.h>
#include <stdexcept>
#include <string>
using namespace std;


class PostgresClientRepository : public IClientRepository {
private:
    PGconn* conn;

    static Client rowToClient(PGresult* res, int row) {
        return Client(
            stoi(PQgetvalue(res, row, 0)),
            PQgetvalue(res, row, 1),
            PQgetvalue(res, row, 2),
            stod(PQgetvalue(res, row, 3))
        );
    }

public:
    explicit PostgresClientRepository(PGconn* dbConn) : conn(dbConn) {}

    int add(Client& client) override {
        const char* sql = "INSERT INTO Clients (name, password, balance) VALUES ($1, $2, $3) RETURNING id;";
        string balanceStr = to_string(client.getBalance());
        const char* params[3] = { client.getName().c_str(), client.getPassword().c_str(), balanceStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 3, nullptr, params, nullptr, nullptr, 0);
        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            string err = PQresultErrorMessage(res);
            PQclear(res);
            throw runtime_error("Failed to insert client: " + err);
        }
        int newId = stoi(PQgetvalue(res, 0, 0));
        PQclear(res);
        client.setId(newId);
        return newId;
    }

    bool update(const Client& client) override {
        const char* sql = "UPDATE Clients SET name=$1, password=$2, balance=$3 WHERE id=$4;";
        string balanceStr = to_string(client.getBalance());
        string idStr = to_string(client.getId());
        const char* params[4] = { client.getName().c_str(), client.getPassword().c_str(),
                                   balanceStr.c_str(), idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 4, nullptr, params, nullptr, nullptr, 0);
        bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
        string affected = ok ? PQcmdTuples(res) : "0";
        PQclear(res);
        return ok && affected != "0" && !affected.empty();
    }

    optional<Client> findById(int id) override {
        const char* sql = "SELECT id, name, password, balance FROM Clients WHERE id=$1;";
        string idStr = to_string(id);
        const char* params[1] = { idStr.c_str() };

        PGresult* res = PQexecParams(conn, sql, 1, nullptr, params, nullptr, nullptr, 0);
        optional<Client> result;
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
            result = rowToClient(res, 0);
        }
        PQclear(res);
        return result;
    }

    vector<Client> getAll() override {
        const char* sql = "SELECT id, name, password, balance FROM Clients;";
        PGresult* res = PQexec(conn, sql);

        vector<Client> results;
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            for (int i = 0; i < PQntuples(res); i++) {
                results.push_back(rowToClient(res, i));
            }
        }
        PQclear(res);
        return results;
    }
};
