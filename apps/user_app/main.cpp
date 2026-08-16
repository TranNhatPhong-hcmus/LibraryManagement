#include <iostream>
#include <string>
#include <limits>

#include "Book.h"
#include "User.h"
#include "Date.h"
#include "BorrowRecord.h"

#include "Library.h"
#include "UserManager.h"
#include "AuthService.h"
#include "BorrowService.h"

#include "BookRepository.h"
#include "UserRepository.h"
#include "BorrowRecordRepository.h"
#include "Admin.h"



void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int inputInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Loi: vui long nhap so!" << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        return value;
    }
}

std::string inputLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

Date inputDate(const std::string& prompt) {
    std::string str = inputLine(prompt);
    return Date::fromString(str);
}



void viewAvailableBooks(Library& library) {
    std::vector<Book> books = library.getAvailableBooks();
    std::cout << "\nSach con trong (" << books.size() << " cuon):" << std::endl;
    for (size_t i = 0; i < books.size(); i++) {
        std::cout << books[i].getBookId() << " | " << books[i].getTitle()
            << " | " << books[i].getAuthor()
            << " | con " << books[i].getAvailableCopies() << " cuon" << std::endl;
    }
}

void borrowBookFlow(BorrowService& borrowService, const std::string& userId,
    BookRepository& bookRepo, Library& library,
    BorrowRecordRepository& recordRepo) {
    std::string bookId = inputLine("Nhap BookId muon muon: ");
    Date borrowDate = inputDate("Ngay muon (DD/MM/YYYY): ");
    Date dueDate = inputDate("Ngay het han (DD/MM/YYYY): ");

    if (borrowService.borrowBook(userId, bookId, borrowDate, dueDate)) {
        bookRepo.saveBooks(library.getAllBooks());
        recordRepo.saveRecords(borrowService.getAllRecords());
        std::cout << "Muon sach thanh cong!" << std::endl;
    }
}

void returnBookFlow(BorrowService& borrowService, const std::string& userId,
    BookRepository& bookRepo, Library& library,
    BorrowRecordRepository& recordRepo) {
    std::vector<BorrowRecord> history = borrowService.getUserHistory(userId);
    std::cout << "\nCac phieu dang muon cua ban:" << std::endl;
    bool hasBorrowing = false;
    for (size_t i = 0; i < history.size(); i++) {
        if (history[i].getStatus() == BorrowStatus::Borrowing) {
            std::cout << history[i].getRecordId() << " | Book: " << history[i].getBookId()
                << " | Han: " << history[i].getDueDate().toString() << std::endl;
            hasBorrowing = true;
        }
    }
    if (!hasBorrowing) {
        std::cout << "(Ban khong co phieu nao dang muon)" << std::endl;
        return;
    }

    std::string recordId = inputLine("Nhap RecordId can tra: ");
    Date returnDate = inputDate("Ngay tra (DD/MM/YYYY): ");

    if (borrowService.returnBook(recordId, returnDate)) {
        bookRepo.saveBooks(library.getAllBooks());
        recordRepo.saveRecords(borrowService.getAllRecords());
        std::cout << "Tra sach thanh cong!" << std::endl;
    }
}

void viewMyHistory(BorrowService& borrowService, const std::string& userId) {
    std::vector<BorrowRecord> history = borrowService.getUserHistory(userId);
    std::cout << "\nLich su muon cua ban (" << history.size() << " phieu):" << std::endl;
    for (size_t i = 0; i < history.size(); i++) {
        std::cout << history[i].getRecordId() << " | Book: " << history[i].getBookId()
            << " | Muon: " << history[i].getBorrowDate().toString()
            << " | Han: " << history[i].getDueDate().toString()
            << " | Trang thai: " << borrowStatusToString(history[i].getStatus())
            << std::endl;
    }
}



int main() {

    BookRepository bookRepo("data/books.txt");
    UserRepository userRepo("data/users.txt");
    BorrowRecordRepository recordRepo("data/records.txt");

    std::vector<Book> loadedBooks = bookRepo.loadBooks();
    std::vector<User> loadedUsers = userRepo.loadUsers();

    Library library;
    for (size_t i = 0; i < loadedBooks.size(); i++) library.addBook(loadedBooks[i]);

    UserManager userManager;
    for (size_t i = 0; i < loadedUsers.size(); i++) userManager.addUser(loadedUsers[i]);

    Admin admin("A001", "Quan Ly Thu Vien", "admin123");
    AuthService authService(userManager, admin);
    BorrowService borrowService(library, userManager);

    // 2. Dang nhap User
    std::cout << "===== LIBRARY USER APP =====" << std::endl;
    std::string userId = inputLine("Nhap UserId de dang nhap: ");
    User* user = authService.loginUser(userId);

    if (!user) {
        std::cout << "Dang nhap that bai. Thoat chuong trinh." << std::endl;
        return 0;
    }

    // 3. Menu chinh
    while (true) {
        std::cout << "\n===== MENU USER =====" << std::endl;
        std::cout << "1. Xem sach con trong" << std::endl;
        std::cout << "2. Muon sach" << std::endl;
        std::cout << "3. Tra sach" << std::endl;
        std::cout << "4. Xem lich su muon" << std::endl;
        std::cout << "0. Logout" << std::endl;
        int choice = inputInt("Chon: ");

        switch (choice) {
        case 1:
            viewAvailableBooks(library);
            break;
        case 2:
            borrowBookFlow(borrowService, userId, bookRepo, library, recordRepo);
            break;
        case 3:
            returnBookFlow(borrowService, userId, bookRepo, library, recordRepo);
            break;
        case 4:
            viewMyHistory(borrowService, userId);
            break;
        case 0:
            bookRepo.saveBooks(library.getAllBooks());
            recordRepo.saveRecords(borrowService.getAllRecords());
            std::cout << "Da luu du lieu. Tam biet!" << std::endl;
            return 0;
        default:
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    }

    return 0;
}