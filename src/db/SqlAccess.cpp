
#include "SqlAccess.h"
#include <iostream>

SqlAccess::SqlAccess(const std::string& db_file) {
    if (sqlite3_open(db_file.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

SqlAccess::~SqlAccess() {
    if (db) sqlite3_close(db);
}

sqlite3* SqlAccess::getDb() {
    return db;
}
