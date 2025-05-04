
#include "MusicSalonService.h"

MusicSalonService::MusicSalonService(DiskRepository* repo) : repository(repo) {}

void MusicSalonService::deliverCD(int cd_id, int amount, const std::string& date) {
    repository->insertTransaction(cd_id, amount, date, "поступление");
}

bool MusicSalonService::sellCD(int cd_id, int amount, const std::string& date) {
    int available = repository->getAvailableCDs(cd_id);
    if (available >= amount) {
        repository->insertTransaction(cd_id, amount, date, "продажа");
        return true;
    }
    return false;
}

std::pair<int, double> MusicSalonService::getSalesReport(int cd_id, const std::string& start_date, const std::string& end_date) {
    return repository->getSalesData(cd_id, start_date, end_date);
}
