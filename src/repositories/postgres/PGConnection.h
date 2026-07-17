#pragma once
#include <libpq-fe.h>
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;


class PGConnection {
private:
    PGconn* conn = nullptr;

    PGConnection(const string& host, const string& port,
                 const string& dbname, const string& user,
                 const string& password) {
        string connInfo =
            "host=" + host +
            " port=" + port +
            " dbname=" + dbname +
            " user=" + user;
        if (!password.empty()) connInfo += " password=" + password;

        conn = PQconnectdb(connInfo.c_str());

        if (PQstatus(conn) != CONNECTION_OK) {
            string err = PQerrorMessage(conn);
            PQfinish(conn);
            throw runtime_error("Failed to connect to PostgreSQL: " + err);
        }

        createTables();
    }

    void createTables() {
        execute(R"(
            CREATE TABLE IF NOT EXISTS Clients (
                id SERIAL PRIMARY KEY,
                name TEXT NOT NULL,
                password TEXT NOT NULL,
                balance DOUBLE PRECISION NOT NULL
            );
        )");

        execute(R"(
            CREATE TABLE IF NOT EXISTS Employees (
                id SERIAL PRIMARY KEY,
                name TEXT NOT NULL,
                password TEXT NOT NULL,
                salary DOUBLE PRECISION NOT NULL
            );
        )");

        execute(R"(
            CREATE TABLE IF NOT EXISTS Admins (
                id SERIAL PRIMARY KEY,
                name TEXT NOT NULL,
                password TEXT NOT NULL,
                salary DOUBLE PRECISION NOT NULL
            );
        )");
    }

public:
    PGConnection(const PGConnection&) = delete;
    PGConnection& operator=(const PGConnection&) = delete;

    
    static PGConnection& getInstance(
        const string& host = "localhost",
        const string& port = "5432",
        const string& dbname = "bank_system",
        const string& user = "",     
        const string& password = "") {
        static PGConnection instance(host, port, dbname,
                                      user.empty() ? getSystemUser() : user, password);
        return instance;
    }

    static string getSystemUser() {
        const char* envUser = getenv("USER");
        return envUser ? envUser : "postgres";
    }

    PGconn* getHandle() const { return conn; }

    void execute(const string& sql) {
        PGresult* res = PQexec(conn, sql.c_str());
        ExecStatusType status = PQresultStatus(res);
        if (status != PGRES_COMMAND_OK && status != PGRES_TUPLES_OK) {
            string err = PQresultErrorMessage(res);
            PQclear(res);
            throw runtime_error("SQL error: " + err);
        }
        PQclear(res);
    }

    ~PGConnection() {
        if (conn) PQfinish(conn);
    }
};
