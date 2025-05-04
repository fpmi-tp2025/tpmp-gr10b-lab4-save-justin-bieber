
#ifndef SQL_ACCESS_H
#define SQL_ACCESS_H

#include <sqlite3.h>
#include <string>

class SqlAccess {
public:
    SqlAccess(const std::string& db_file);
    ~SqlAccess();

    sqlite3* getDb();

private:
    sqlite3* db;
};

#endif
