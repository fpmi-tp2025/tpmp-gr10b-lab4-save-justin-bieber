
#ifndef DISK_REPOSITORY_H
#define DISK_REPOSITORY_H

#include "../db/SqlAccess.h"
#include <string>
#include <utility>

class DiskRepository {
public:
    DiskRepository(SqlAccess* access);
    void insertTransaction(int cd_id, int amount, const std::string& date, const std::string& type);
    int getAvailableCDs(int cd_id);
    std::pair<int, double> getSalesData(int cd_id, const std::string& start_date, const std::string& end_date);

private:
    SqlAccess* dbAccess;
};

#endif
