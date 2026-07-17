#pragma once
#include "../interfaces/ITransactionManager.h"
#include <libpq-fe.h>
#include <stdexcept>
#include <string>
using namespace std;

class PostgresTransactionManager : public ITransactionManager {
private:
    PGconn* conn;

    void execute(const char* sql) {
        PGresult* res = PQexec(conn, sql);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            string err = PQresultErrorMessage(res);
            PQclear(res);
            throw runtime_error("Transaction error: " + err);
        }
        PQclear(res);
    }

public:
    explicit PostgresTransactionManager(PGconn* conn) : conn(conn) {}

    void begin() override { execute("BEGIN;"); }
    void commit() override { execute("COMMIT;"); }
    void rollback() override { execute("ROLLBACK;"); }
};
