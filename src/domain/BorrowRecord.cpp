#include "BorrowRecord.h"
#include <iostream>
#include <string>

std::string borrowStatusToString(BorrowStatus status) {
    if (status == BorrowStatus::Borrowing) return "Borrowing";
    if (status == BorrowStatus::Returned) return "Returned";
    return "Overdue";
}

BorrowStatus stringToBorrowStatus(const std::string& str) {
    if (str == "Borrowing") return BorrowStatus::Borrowing;
    if (str == "Returned") return BorrowStatus::Returned;
    return BorrowStatus::Overdue;
}

BorrowRecord::BorrowRecord(const std::string& recordId, const std::string& userId, const std::string& bookId,
    const Date& borrowDate, const Date& dueDate)
    : recordId(recordId), userId(userId), bookId(bookId),
    borrowDate(borrowDate), dueDate(dueDate),
    returnDate(0, 0, 0),
    status(BorrowStatus::Borrowing)
{
}

BorrowRecord::BorrowRecord(const std::string& recordId, const std::string& userId, const std::string& bookId,
    const Date& borrowDate, const Date& dueDate, const Date& returnDate, BorrowStatus status)
    : recordId(recordId), userId(userId), bookId(bookId),
    borrowDate(borrowDate), dueDate(dueDate),
    returnDate(returnDate),
    status(status) {
}

bool BorrowRecord::markReturned(const Date& returnDate) {
    if (status == BorrowStatus::Returned) {
        std::cout << "Loi: phieu nay da duoc tra roi!" << std::endl;
        return false;
    }
    if (!returnDate.isValid()) {
        std::cout << "Loi: ngay tra khong hop le!" << std::endl;
        return false;
    }

    if (isOverdue(returnDate)) {
        std::cout << "Luu y: tra sach tre han!" << std::endl;
    }

    this->returnDate = returnDate;
    status = BorrowStatus::Returned;
    return true;
}

bool BorrowRecord::isOverdue(const Date& currentDate) const {
    return currentDate > dueDate;
}