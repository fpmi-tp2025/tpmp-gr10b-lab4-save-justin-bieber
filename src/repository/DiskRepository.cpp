
#include "DiskRepository.h"
#include <sqlite3.h>
#include <string>
#include <iostream>

DiskRepository::DiskRepository(SqlAccess* access) : dbAccess(access) {}

void DiskRepository::insertTransaction(int cd_id, int amount, const std::string& date, const std::string& type) {
    std::string sql = "INSERT INTO Transactions (date, amount, type, cd_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(dbAccess->getDb(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, amount);
    sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, cd_id);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        std::cerr << "Error inserting transaction" << std::endl;
    sqlite3_finalize(stmt);
}

int DiskRepository::getAvailableCDs(int cd_id) {
    std::string sql = "SELECT "
                      "(SELECT IFNULL(SUM(amount), 0) FROM Transactions WHERE cd_id = ? AND type = 'поступление') - "
                      "(SELECT IFNULL(SUM(amount), 0) FROM Transactions WHERE cd_id = ? AND type = 'продажа')";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(dbAccess->getDb(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, cd_id);
    sqlite3_bind_int(stmt, 2, cd_id);
    int result = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        result = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return result;
}

std::pair<int, double> DiskRepository::getSalesData(int cd_id, const std::string& start_date, const std::string& end_date) {
    std::string sql = "SELECT SUM(t.amount), SUM(t.amount * c.price) "
                      "FROM Transactions t JOIN CD c ON t.cd_id = c.cd_id "
                      "WHERE t.cd_id = ? AND t.type = 'продажа' AND t.date BETWEEN ? AND ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(dbAccess->getDb(), sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, cd_id);
    sqlite3_bind_text(stmt, 2, start_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, end_date.c_str(), -1, SQLITE_STATIC);
    int amount = 0;
    double income = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        amount = sqlite3_column_int(stmt, 0);
        income = sqlite3_column_double(stmt, 1);
    }
    sqlite3_finalize(stmt);
    return {amount, income};
}
