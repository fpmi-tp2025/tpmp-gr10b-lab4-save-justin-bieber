
#include <iostream>
#include "src/db/SqlAccess.h"
#include "src/repository/DiskRepository.h"
#include "src/service/MusicSalonService.h"

int main() {
    SqlAccess db("baby_records.db");
    DiskRepository repo(&db);
    MusicSalonService service(&repo);

    service.deliverCD(1, 10, "2025-05-01");
    if (service.sellCD(1, 3, "2025-05-02")) {
        std::cout << "Продажа успешна\n";
    } else {
        std::cout << "Недостаточно дисков на складе\n";
    }

    auto [sold, income] = service.getSalesReport(1, "2025-05-01", "2025-05-31");
    std::cout << "Продано: " << sold << ", доход: " << income << std::endl;

    return 0;
}
