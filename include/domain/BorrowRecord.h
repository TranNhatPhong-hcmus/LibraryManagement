#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include<string>
#include "Date.h"

enum class BorrowStatus { Borrowing, Returned, Overdue };



std::string borrowStatusToString(BorrowStatus status);
BorrowStatus stringToBorrowStatus(const std::string& str);

class BorrowRecord {
private:
    std::string recordId;
    std::string userId;
    std::string bookId;
    Date borrowDate;
    Date dueDate;
    Date returnDate;
    BorrowStatus status;
public:
    BorrowRecord(const std::string& recordId, const std::string& userId, const std::string& bookId,
        const Date& borrowDate, const Date& dueDate);

    BorrowRecord(const std::string& recordId, const std::string& userId, const std::string& bookId,
        const Date& borrowDate, const Date& dueDate, const Date& returnDate, BorrowStatus status);

    const std::string& getRecordId() const { return recordId; }
    const std::string& getUserId() const { return userId; }
    const std::string& getBookId() const { return bookId; }
    const Date& getBorrowDate() const { return borrowDate; }
    const Date& getDueDate() const { return dueDate; }
    const Date& getReturnDate() const { return returnDate; }
    BorrowStatus getStatus() const { return status; }

    bool markReturned(const Date& returnDate);
    bool isOverdue(const Date& currentDate) const;
};



#endif