
#ifndef MUSIC_SALON_SERVICE_H
#define MUSIC_SALON_SERVICE_H

#include "../repository/DiskRepository.h"
#include <string>
#include <utility>

class MusicSalonService {
public:
    MusicSalonService(DiskRepository* repo);
    void deliverCD(int cd_id, int amount, const std::string& date);
    bool sellCD(int cd_id, int amount, const std::string& date);
    std::pair<int, double> getSalesReport(int cd_id, const std::string& start_date, const std::string& end_date);

private:
    DiskRepository* repository;
};

#endif
