#include "baby_record_store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Basic CRUD operations
void add_cd(sqlite3* db, const char* manufacturer, const char* 
release_date, float price) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO CD (manufacturer, release_date, price) 
VALUES (?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, manufacturer, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, release_date, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, price);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void add_song(sqlite3* db, const char* song_name, const char* author, 
              const char* performer, int cd_id) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Songs (song_name, author, performer, 
cd_id) VALUES (?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, song_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, performer, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, cd_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void add_transaction(sqlite3* db, const char* date, int amount, const 
char* type, int cd_id) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Transactions (date, amount, type, 
cd_id) VALUES (?, ?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, amount);
    sqlite3_bind_text(stmt, 3, type, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, cd_id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// Reporting functions
void get_cd_inventory(sqlite3* db) {
    const char* sql =
        "SELECT c.cd_id, c.manufacturer, c.release_date, c.price, "
        "SUM(CASE WHEN t.type='поступление' THEN t.amount ELSE 0 END) - "
        "SUM(CASE WHEN t.type='продажа' THEN t.amount ELSE 0 END) AS 
remaining "
        "FROM CD c LEFT JOIN Transactions t ON c.cd_id = t.cd_id "
        "GROUP BY c.cd_id ORDER BY remaining DESC;";

    sqlite3_exec(db, sql, callback_print, 0, NULL);
}

void get_cd_sales_period(sqlite3* db, int cd_id, const char* start_date, 
const char* end_date) {
    sqlite3_stmt* stmt;
    const char* sql =
        "SELECT SUM(amount), SUM(amount * (SELECT price FROM CD WHERE 
cd_id = ?1)) "
        "FROM Transactions WHERE cd_id = ?1 AND type = 'продажа' AND date 
BETWEEN ?2 AND ?3;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, cd_id);
    sqlite3_bind_text(stmt, 2, start_date, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, end_date, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Quantity sold: %d, Total value: %.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_double(stmt, 1));
    }
    sqlite3_finalize(stmt);
}

// Validation
void validate_sale(sqlite3* db, int cd_id, int quantity) {
    sqlite3_stmt* stmt;
    const char* sql =
        "SELECT (" 
        "  (SELECT COALESCE(SUM(amount), 0) FROM Transactions WHERE cd_id 
= ?1 AND type = 'поступление') - "
        "  (SELECT COALESCE(SUM(amount), 0) FROM Transactions WHERE cd_id 
= ?1 AND type = 'продажа')"
        ") >= ?2;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, cd_id);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if (sqlite3_column_int(stmt, 0) == 0) {
            fprintf(stderr, "Error: Not enough inventory for CD %d\n", 
cd_id);
            exit(1);
        }
    }
    sqlite3_finalize(stmt);
}

// Helper function for printing query results
static int callback_print(void* data, int argc, char argv, char azColName) 
{
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
