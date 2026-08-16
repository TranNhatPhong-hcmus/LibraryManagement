#ifndef BORROW_SERVICE_H
#define BORROW_SERVICE_H

#include <vector>
#include <string>
#include "BorrowRecord.h"
#include "Library.h"
#include "UserManager.h"
#include "Date.h"

class BorrowService {
private:
    std::vector<BorrowRecord> records;
    Library& library;
    UserManager& userManager;

public:
    BorrowService(Library& library, UserManager& userManager);

    bool borrowBook(const std::string& userId, const std::string& bookId,
        const Date& borrowDate, const Date& dueDate);
    bool returnBook(const std::string& recordId, const Date& returnDate);

    std::vector<BorrowRecord> getUserHistory(const std::string& userId) const;
    std::vector<BorrowRecord> getAllRecords() const;
    BorrowRecord* findRecordById(const std::string& recordId);
};

#endif