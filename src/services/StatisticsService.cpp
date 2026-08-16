#include "StatisticsService.h"
#include <map>

int StatisticsService::countBorrowingBooks(const std::vector<BorrowRecord>& records) const {
    int count = 0;
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].getStatus() == BorrowStatus::Borrowing) {
            count++;
        }
    }
    return count;
}


std::string StatisticsService::getMostFrequentKey(const std::vector<BorrowRecord>& records, int keyType) const {
    if (records.empty()) {
        return "";
    }

    std::map<std::string, int> countMap;
    for (size_t i = 0; i < records.size(); i++) {
        std::string key = (keyType == 0) ? records[i].getUserId() : records[i].getBookId();
        countMap[key]++;
    }

    std::string bestKey = "";
    int maxCount = 0;
    for (std::map<std::string, int>::iterator it = countMap.begin(); it != countMap.end(); ++it) {
        if (it->second > maxCount) {
            maxCount = it->second;
            bestKey = it->first;
        }
    }
    return bestKey;
}

std::string StatisticsService::getTopBorrower(const std::vector<BorrowRecord>& records) const {
    return getMostFrequentKey(records, 0);   // 0 = dem theo userId
}

std::string StatisticsService::getMostBorrowedBook(const std::vector<BorrowRecord>& records) const {
    return getMostFrequentKey(records, 1);   // 1 = dem theo bookId
}

int StatisticsService::getOverdueCount(const std::vector<BorrowRecord>& records, const Date& currentDate) const {
    int count = 0;
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].getStatus() == BorrowStatus::Borrowing && records[i].isOverdue(currentDate)) {
            count++;
        }
    }
    return count;
}