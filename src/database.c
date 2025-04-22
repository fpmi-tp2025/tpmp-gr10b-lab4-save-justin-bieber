#include "database.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3* connect_db(const char* db_name) {
    sqlite3* db;
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    return db;
}

void disconnect_db(sqlite3* db) {
    sqlite3_close(db);
}

void execute_query(sqlite3* db, const char* query) {
    char* err_msg = 0;
    if (sqlite3_exec(db, query, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}
