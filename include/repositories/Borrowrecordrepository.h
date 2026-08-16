#ifndef BORROW_RECORD_REPOSITORY_H
#define BORROW_RECORD_REPOSITORY_H

#include <vector>
#include <string>
#include "BorrowRecord.h"

class BorrowRecordRepository {
private:
    std::string filePath;

public:
    BorrowRecordRepository(const std::string& filePath);

    std::vector<BorrowRecord> loadRecords();
    bool saveRecords(const std::vector<BorrowRecord>& records);
};

#endif