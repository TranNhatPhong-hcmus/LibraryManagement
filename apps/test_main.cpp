#include "Book.h"
#include "User.h"
#include "Date.h"
#include "BorrowRecord.h"
#include <iostream>

int main() {
    std::cout << "===== TEST BOOK =====" << std::endl;
    Book b1("B001", "Clean Code", "Robert Martin", "Cong Nghe", 5);
    std::cout << "BookId: " << b1.getBookId() << std::endl;
    std::cout << "Title: " << b1.getTitle() << std::endl;
    std::cout << "Author: " << b1.getAuthor() << std::endl;
    std::cout << "Category: " << b1.getCategory() << std::endl;
    std::cout << "TotalCopies: " << b1.getTotalCopies() << std::endl;
    std::cout << "AvailableCopies: " << b1.getAvailableCopies() << std::endl;

    std::cout << "\n-- Test decreaseAvailable() --" << std::endl;
    for (int i = 0; i < 6; i++) {
        bool ok = b1.decreaseAvailable();
        std::cout << "Lan " << i + 1 << ": ok=" << ok
            << " | availableCopies=" << b1.getAvailableCopies() << std::endl;
    }

    std::cout << "\n-- Test increaseAvailable() --" << std::endl;
    for (int i = 0; i < 6; i++) {
        bool ok = b1.increaseAvailable();
        std::cout << "Lan " << i + 1 << ": ok=" << ok
            << " | availableCopies=" << b1.getAvailableCopies() << std::endl;
    }

    std::cout << "\n-- Test setTotalCopies() --" << std::endl;
    b1.decreaseAvailable();
    b1.decreaseAvailable();
    b1.decreaseAvailable();
    std::cout << "Truoc: total=" << b1.getTotalCopies() << " available=" << b1.getAvailableCopies() << std::endl;

    std::cout << "Thu giam total xuong 1 (dang co 3 cuon muon, phai bi chan):" << std::endl;
    b1.setTotalCopies(1);
    std::cout << "Sau: total=" << b1.getTotalCopies() << " available=" << b1.getAvailableCopies() << std::endl;

    std::cout << "Thu tang total len 8 (hop le):" << std::endl;
    b1.setTotalCopies(8);
    std::cout << "Sau: total=" << b1.getTotalCopies() << " available=" << b1.getAvailableCopies() << std::endl;


    std::cout << "\n===== TEST USER =====" << std::endl;
    User u1("U001", "Nguyen Van A", UserRole::Student, "a@gmail.com");
    std::cout << "UserId: " << u1.getUserId() << std::endl;
    std::cout << "Name: " << u1.getName() << std::endl;
    std::cout << "Email: " << u1.getEmail() << std::endl;

    std::cout << "\n-- Test setName('') (phai bi chan) --" << std::endl;
    u1.setName("");
    std::cout << "Name sau khi thu doi rong: " << u1.getName() << std::endl;

    std::cout << "\n-- Test setName hop le --" << std::endl;
    u1.setName("Nguyen Van B");
    std::cout << "Name sau khi doi: " << u1.getName() << std::endl;


    std::cout << "\n===== TEST DATE =====" << std::endl;
    Date d1(15, 3, 2026);
    Date d2(20, 1, 2026);
    std::cout << "d1 = " << d1.toString() << std::endl;
    std::cout << "d2 = " << d2.toString() << std::endl;
    std::cout << "d1 > d2 ? " << (d1 > d2 ? "true" : "false") << " (phai la true)" << std::endl;
    std::cout << "d2 > d1 ? " << (d2 > d1 ? "true" : "false") << " (phai la false)" << std::endl;

    std::cout << "\n-- Test fromString --" << std::endl;
    Date d3 = Date::fromString("15/03/2026");
    std::cout << "d3 = " << d3.toString() << " (phai giong d1)" << std::endl;

    std::cout << "\n-- Test isValid --" << std::endl;
    Date invalidDate(31, 4, 2026); // thang 4 khong co ngay 31
    std::cout << "31/04/2026 isValid? " << (invalidDate.isValid() ? "true" : "false") << " (phai la false)" << std::endl;


    std::cout << "\n===== TEST BORROW RECORD =====" << std::endl;
    BorrowRecord r1("R001", u1.getUserId(), b1.getBookId(), Date(1, 1, 2026), Date(15, 1, 2026));
    std::cout << "RecordId: " << r1.getRecordId() << std::endl;
    std::cout << "UserId: " << r1.getUserId() << std::endl;
    std::cout << "BookId: " << r1.getBookId() << std::endl;
    std::cout << "BorrowDate: " << r1.getBorrowDate().toString() << std::endl;
    std::cout << "DueDate: " << r1.getDueDate().toString() << std::endl;

    std::cout << "\n-- Test markReturned tre han (20/01/2026 > dueDate 15/01/2026) --" << std::endl;
    bool ok1 = r1.markReturned(Date(20, 1, 2026));
    std::cout << "Ket qua markReturned lan 1: " << ok1 << std::endl;
    std::cout << "ReturnDate: " << r1.getReturnDate().toString() << std::endl;

    std::cout << "\n-- Test markReturned lan 2 (phai bi chan vi da tra roi) --" << std::endl;
    bool ok2 = r1.markReturned(Date(25, 1, 2026));
    std::cout << "Ket qua markReturned lan 2: " << ok2 << " (phai la false)" << std::endl;

    return 0;
}