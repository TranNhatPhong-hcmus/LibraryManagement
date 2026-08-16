#include <iostream>
#include <string>
#include <limits>

#include "Book.h"
#include "User.h"
#include "Admin.h"
#include "Date.h"
#include "BorrowRecord.h"

#include "Library.h"
#include "UserManager.h"
#include "AuthService.h"
#include "BorrowService.h"
#include "StatisticsService.h"

#include "BookRepository.h"
#include "UserRepository.h"
#include "BorrowRecordRepository.h"

// ===== Ham tien ich cho UI =====

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

// ===== Cac man hinh con =====

void manageBooks(Library& library, BookRepository& bookRepo) {
    while (true) {
        std::cout << "\n----- QUAN LY SACH -----" << std::endl;
        std::cout << "1. Them sach" << std::endl;
        std::cout << "2. Sua sach" << std::endl;
        std::cout << "3. Xoa sach" << std::endl;
        std::cout << "4. Danh sach tat ca sach" << std::endl;
        std::cout << "0. Quay lai" << std::endl;
        int choice = inputInt("Chon: ");

        if (choice == 1) {
            std::string bookId = inputLine("BookId: ");
            std::string title = inputLine("Ten sach: ");
            std::string author = inputLine("Tac gia: ");
            std::string category = inputLine("The loai: ");
            int total = inputInt("So luong: ");

            library.addBook(Book(bookId, title, author, category, total));
            bookRepo.saveBooks(library.getAllBooks());
            std::cout << "Da them sach (neu khong co loi o tren)." << std::endl;
        }
        else if (choice == 2) {
            std::string bookId = inputLine("Nhap BookId can sua: ");
            std::string title = inputLine("Ten sach moi: ");
            std::string author = inputLine("Tac gia moi: ");
            std::string category = inputLine("The loai moi: ");
            int total = inputInt("Tong so luong moi: ");

            if (library.updateBook(bookId, title, author, category, total)) {
                bookRepo.saveBooks(library.getAllBooks());
                std::cout << "Cap nhat thanh cong!" << std::endl;
            }
        }
        else if (choice == 3) {
            std::string bookId = inputLine("Nhap BookId can xoa: ");
            if (library.removeBook(bookId)) {
                bookRepo.saveBooks(library.getAllBooks());
                std::cout << "Xoa thanh cong!" << std::endl;
            }
            else {
                std::cout << "Khong tim thay sach!" << std::endl;
            }
        }
        else if (choice == 4) {
            std::vector<Book> books = library.getAllBooks();
            std::cout << "\nTong so: " << books.size() << " sach" << std::endl;
            for (size_t i = 0; i < books.size(); i++) {
                std::cout << books[i].getBookId() << " | " << books[i].getTitle()
                    << " | " << books[i].getAuthor() << " | " << books[i].getCategory()
                    << " | con " << books[i].getAvailableCopies() << "/" << books[i].getTotalCopies()
                    << std::endl;
            }
        }
        else if (choice == 0) {
            return;
        }
        else {
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    }
}

void manageUsers(UserManager& userManager, UserRepository& userRepo) {
    while (true) {
        std::cout << "\n----- QUAN LY NGUOI DUNG -----" << std::endl;
        std::cout << "1. Them user" << std::endl;
        std::cout << "2. Sua user" << std::endl;
        std::cout << "3. Xoa user" << std::endl;
        std::cout << "4. Danh sach tat ca user" << std::endl;
        std::cout << "0. Quay lai" << std::endl;
        int choice = inputInt("Chon: ");

        if (choice == 1) {
            std::string userId = inputLine("UserId: ");
            std::string name = inputLine("Ho ten: ");
            std::string roleStr = inputLine("Vai tro (Student/Teacher): ");
            std::string email = inputLine("Email: ");

            userManager.addUser(User(userId, name, stringToUserRole(roleStr), email));
            userRepo.saveUsers(userManager.getAllUsers());
            std::cout << "Da them user (neu khong co loi o tren)." << std::endl;
        }
        else if (choice == 2) {
            std::string userId = inputLine("Nhap UserId can sua: ");
            std::string name = inputLine("Ho ten moi: ");
            std::string email = inputLine("Email moi: ");

            if (userManager.updateUser(userId, name, email)) {
                userRepo.saveUsers(userManager.getAllUsers());
                std::cout << "Cap nhat thanh cong!" << std::endl;
            }
        }
        else if (choice == 3) {
            std::string userId = inputLine("Nhap UserId can xoa: ");
            if (userManager.removeUser(userId)) {
                userRepo.saveUsers(userManager.getAllUsers());
                std::cout << "Xoa thanh cong!" << std::endl;
            }
            else {
                std::cout << "Khong tim thay user!" << std::endl;
            }
        }
        else if (choice == 4) {
            std::vector<User> users = userManager.getAllUsers();
            std::cout << "\nTong so: " << users.size() << " user" << std::endl;
            for (size_t i = 0; i < users.size(); i++) {
                std::cout << users[i].getUserId() << " | " << users[i].getName()
                    << " | " << userRoleToString(users[i].getRole())
                    << " | " << users[i].getEmail() << std::endl;
            }
        }
        else if (choice == 0) {
            return;
        }
        else {
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    }
}

void viewBorrowRecords(BorrowService& borrowService) {
    std::vector<BorrowRecord> records = borrowService.getAllRecords();
    std::cout << "\nTong so phieu muon: " << records.size() << std::endl;
    for (size_t i = 0; i < records.size(); i++) {
        std::cout << records[i].getRecordId() << " | User: " << records[i].getUserId()
            << " | Book: " << records[i].getBookId()
            << " | Muon: " << records[i].getBorrowDate().toString()
            << " | Han: " << records[i].getDueDate().toString()
            << " | Trang thai: " << borrowStatusToString(records[i].getStatus())
            << std::endl;
    }
}

void showStatistics(BorrowService& borrowService, StatisticsService& statsService) {
    std::vector<BorrowRecord> records = borrowService.getAllRecords();

    std::cout << "\n----- THONG KE -----" << std::endl;
    std::cout << "So sach dang duoc muon: " << statsService.countBorrowingBooks(records) << std::endl;

    std::string topBorrower = statsService.getTopBorrower(records);
    std::cout << "Nguoi muon nhieu nhat: " << (topBorrower.empty() ? "(chua co du lieu)" : topBorrower) << std::endl;

    std::string mostBorrowedBook = statsService.getMostBorrowedBook(records);
    std::cout << "Sach duoc muon nhieu nhat: " << (mostBorrowedBook.empty() ? "(chua co du lieu)" : mostBorrowedBook) << std::endl;

    Date today = inputDate("Nhap ngay hom nay (DD/MM/YYYY) de tinh qua han: ");
    std::cout << "So phieu qua han: " << statsService.getOverdueCount(records, today) << std::endl;
}

// ===== main =====

int main() {
    // 1. Load du lieu tu file
    BookRepository bookRepo("data/books.txt");
    UserRepository userRepo("data/users.txt");
    BorrowRecordRepository recordRepo("data/records.txt");

    std::vector<Book> loadedBooks = bookRepo.loadBooks();
    std::vector<User> loadedUsers = userRepo.loadUsers();
    std::vector<BorrowRecord> loadedRecords = recordRepo.loadRecords();

    // 2. Dua du lieu vao cac class quan ly
    Library library;
    for (size_t i = 0; i < loadedBooks.size(); i++) library.addBook(loadedBooks[i]);

    UserManager userManager;
    for (size_t i = 0; i < loadedUsers.size(); i++) userManager.addUser(loadedUsers[i]);

    // Admin hard-code (chua co AdminRepository)
    Admin admin("A001", "Quan Ly Thu Vien", "admin123");

    AuthService authService(userManager, admin);
    BorrowService borrowService(library, userManager);
    StatisticsService statisticsService;

    // Nap lai cac phieu muon da co (neu ban muon giu nguyen id dem tiep,
    // co the can chinh BorrowService de nhan vector<BorrowRecord> ban dau -
    // hien tai bo qua buoc nay de giu vi du don gian)

    // 3. Dang nhap Admin
    std::cout << "===== LIBRARY ADMIN APP =====" << std::endl;
    std::string adminId = inputLine("Admin ID: ");
    std::string password = inputLine("Password: ");

    if (!authService.loginAdmin(adminId, password)) {
        std::cout << "Sai thong tin dang nhap. Thoat chuong trinh." << std::endl;
        return 0;
    }

    // 4. Menu chinh
    while (true) {
        std::cout << "\n===== MENU ADMIN =====" << std::endl;
        std::cout << "1. Quan ly sach" << std::endl;
        std::cout << "2. Quan ly nguoi dung" << std::endl;
        std::cout << "3. Xem phieu muon" << std::endl;
        std::cout << "4. Thong ke" << std::endl;
        std::cout << "0. Exit" << std::endl;
        int choice = inputInt("Chon: ");

        switch (choice) {
        case 1:
            manageBooks(library, bookRepo);
            break;
        case 2:
            manageUsers(userManager, userRepo);
            break;
        case 3:
            viewBorrowRecords(borrowService);
            break;
        case 4:
            showStatistics(borrowService, statisticsService);
            break;
        case 0:
            // Luu lai lan cuoi truoc khi thoat
            bookRepo.saveBooks(library.getAllBooks());
            userRepo.saveUsers(userManager.getAllUsers());
            recordRepo.saveRecords(borrowService.getAllRecords());
            std::cout << "Da luu du lieu. Tam biet!" << std::endl;
            return 0;
        default:
            std::cout << "Lua chon khong hop le!" << std::endl;
        }
    }

    return 0;
}