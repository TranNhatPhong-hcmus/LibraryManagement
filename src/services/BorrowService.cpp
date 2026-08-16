#include <vector>
#include <string>
#include <iostream>
#include "BorrowRecord.h"
#include "Library.h"
#include "UserManager.h"
#include "Date.h"
#include "BorrowService.h"

BorrowService::BorrowService(Library& library, UserManager& userManager)
    : library(library), userManager(userManager) {
}

bool BorrowService::borrowBook(const std::string& userId, const std::string& bookId,
    const Date& borrowDate, const Date& dueDate) {

    if (!userManager.findUserById(userId)) {
        std::cout << "Loi: khong ton tai userId: " << userId << std::endl;
        return false;
    }

    Book* book = library.findBookById(bookId);
    if (!book) {
        std::cout << "Loi: khong ton tai sach!" << std::endl;
        return false;
    }

    if (!book->decreaseAvailable()) {
        return false;
    }

    std::string recordId = "R" + std::to_string(records.size() + 1);
    records.push_back(BorrowRecord(recordId, userId, bookId, borrowDate, dueDate));
    return true;
}

bool BorrowService::returnBook(const std::string& recordId, const Date& returnDate) {
    BorrowRecord* record = findRecordById(recordId);
    if (!record) {
        std::cout << "Loi: khong tim thay record" << std::endl;
        return false;
    }

    if (!record->markReturned(returnDate)) {
        return false;
    }

    Book* book = library.findBookById(record->getBookId());
    if (!book) {
        std::cout << "Loi: khong tim thay sach ung voi record nay!" << std::endl;
        return false;
    }
    book->increaseAvailable();
    return true;
}

std::vector<BorrowRecord> BorrowService::getUserHistory(const std::string& userId) const {
    std::vector<BorrowRecord> result;
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].getUserId() == userId) result.push_back(records[i]);
    }
    return result;
}

std::vector<BorrowRecord> BorrowService::getAllRecords() const {
    return records;
}

BorrowRecord* BorrowService::findRecordById(const std::string& recordId) {
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].getRecordId() == recordId) return &records[i];
    }
    return nullptr;
}