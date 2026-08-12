#include "BorrowRecord.h"
#include <iostream>
#include <string>

BorrowRecord::BorrowRecord(const std::string& recordId, const std::string& userId, const std::string bookId,
    const std::string& borrowDate, const std::string& dueDate)
{
    this->recordId = recordId;
    this->userId = userId;
    this->bookId = bookId;
    this->borrowDate = borrowDate;
    this->dueDate = dueDate;
    this->returnDate = "";
    this->status = BorrowStatus::Borrowing;
}

bool BorrowRecord::markReturned(const std::string& returnDate) {
    if (status == BorrowStatus::Returned) {
        std::cout << "Loi: phieu nay da duoc tra roi!" << std::endl;
        return false;
    }
    if (returnDate.empty()) {
        std::cout << "Loi: ngay tra khong duoc rong!" << std::endl;
        return false;
    }

    if (isOverdue(returnDate)) {
        std::cout << "Luu y: tra sach tre han!" << std::endl;
    }

    this->returnDate = returnDate;
    status = BorrowStatus::Returned;
    return true;
}
bool BorrowRecord::isOverdue(const std::string& currentDate) const {
    return currentDate > dueDate;
}

