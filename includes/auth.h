#ifndef AUTH_H
#define AUTH_H

#include <sqlite3.h>
#include <stdbool.h>

bool register_user(sqlite3* db, const char* username, const char* 
password, const char* role);
bool login_user(sqlite3* db, const char* username, const char* password, 
char* role);

#endif // AUTH_H
