#include "BookRepository.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>

BookRepository::BookRepository(const std::string& filePath) : filePath(filePath) {}

std::vector<Book> BookRepository::loadBooks() {
    std::vector<Book> books;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de doc!" << std::endl;
        return books;   // tra ve vector rong, khong crash
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;   // bo qua dong trong (neu co)

        std::vector<std::string> parts = split(line, '|');
        if (parts.size() != 6) {
            std::cout << "Loi: dong du lieu khong hop le, bo qua: " << line << std::endl;
            continue;
        }

        std::string bookId = parts[0];
        std::string title = parts[1];
        std::string author = parts[2];
        std::string category = parts[3];
        int totalCopies = std::stoi(parts[4]);
        int availableCopies = std::stoi(parts[5]);

        books.push_back(Book(bookId, title, author, category, totalCopies, availableCopies));
    }

    file.close();
    return books;
}

bool BookRepository::saveBooks(const std::vector<Book>& books) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de ghi!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < books.size(); i++) {
        file << books[i].getBookId() << "|"
            << books[i].getTitle() << "|"
            << books[i].getAuthor() << "|"
            << books[i].getCategory() << "|"
            << books[i].getTotalCopies() << "|"
            << books[i].getAvailableCopies() << "\n";
    }

    file.close();
    return true;
}