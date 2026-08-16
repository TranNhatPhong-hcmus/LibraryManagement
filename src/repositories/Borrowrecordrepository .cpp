#include "BorrowRecordRepository.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>

BorrowRecordRepository::BorrowRecordRepository(const std::string& filePath) : filePath(filePath) {}

std::vector<BorrowRecord> BorrowRecordRepository::loadRecords() {
    std::vector<BorrowRecord> records;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de doc!" << std::endl;
        return records;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> parts = split(line, '|');
        if (parts.size() != 7) {
            std::cout << "Loi: dong du lieu khong hop le, bo qua: " << line << std::endl;
            continue;
        }

        std::string recordId = parts[0];
        std::string userId = parts[1];
        std::string bookId = parts[2];
        Date borrowDate = Date::fromString(parts[3]);
        Date dueDate = Date::fromString(parts[4]);
        Date returnDate = Date::fromString(parts[5]);   // se la Date(0,0,0) neu chua tra
        BorrowStatus status = stringToBorrowStatus(parts[6]);

        records.push_back(BorrowRecord(recordId, userId, bookId, borrowDate, dueDate, returnDate, status));
    }

    file.close();
    return records;
}

bool BorrowRecordRepository::saveRecords(const std::vector<BorrowRecord>& records) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de ghi!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < records.size(); i++) {
        file << records[i].getRecordId() << "|"
            << records[i].getUserId() << "|"
            << records[i].getBookId() << "|"
            << records[i].getBorrowDate().toString() << "|"
            << records[i].getDueDate().toString() << "|"
            << records[i].getReturnDate().toString() << "|"
            << borrowStatusToString(records[i].getStatus()) << "\n";
    }

    file.close();
    return true;
}