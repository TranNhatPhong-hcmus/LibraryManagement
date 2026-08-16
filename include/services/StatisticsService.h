#ifndef STATISTICS_SERVICE_H
#define STATISTICS_SERVICE_H    

#include <string>
#include <vector>
#include "BorrowRecord.h"

class StatisticsService {
private:
    std::string getMostFrequentKey(const std::vector<BorrowRecord>& records, int keyType) const;
public:
    int countBorrowingBooks(const std::vector<BorrowRecord>& records) const;
    std::string getTopBorrower(const std::vector<BorrowRecord>& records) const;
    std::string getMostBorrowedBook(const std::vector<BorrowRecord>& records) const;
    int getOverdueCount(const std::vector<BorrowRecord>& records, const Date& currentDate) const;
};


#endif