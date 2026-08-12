#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include<iostream>

enum class BorrowStatus { Borrowing, Returned, Overdue };

// Dinh dang date : xx/xx/xxxx

class BorrowRecord {
private:
    std::string recordId;
    std::string userId;
    std::string bookId;
    std::string borrowDate;
    std::string dueDate;
    std::string returnDate;
    BorrowStatus status;
public:
    BorrowRecord(const std::string& recordId, const std::string& userId, const std::string bookId,
        const std::string& borrowDate, const std::string& dueDate);

    const std::string& getRecordId() const { return recordId; }
    const std::string& getUserId() const { return userId; }
    const std::string& getBookId() const { return bookId; }
    const std::string& getBorrowDate() const { return borrowDate; }
    const std::string& getDueDate() const { return dueDate; }
    const std::string& getReturnDate() const { return returnDate; }
    BorrowStatus getStatus() const { return status; }

    bool markReturned(const std::string& returnDate);
    bool isOverdue(const std::string& currentDate) const;
};



#endif