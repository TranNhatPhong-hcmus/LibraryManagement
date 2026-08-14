#include "Library.h"
#include <string>
#include <iostream>
#include <vector>


Library::Library() {}

void Library::addBook(const Book& book) {
    if (findBookById(book.getBookId())) {
        std::cout << "Loi: sach nay da ton tai!";
        return;
    }
    books.push_back(book);
}

bool Library::removeBook(const std::string& bookId) {
    for (size_t i = 0; i < books.size(); i++) {
        if (bookId == books[i].getBookId()) {
            books.erase(books.begin() + i);
            return true;
        }
    }
    return false;
}

// update chi dung cho nhung quyen sach da ton tai
bool Library::updateBook(const std::string& bookId, const std::string& title, const std::string& author,
    const std::string& category, int totalCopies) {
    Book* book = findBookById(bookId);
    if (!book) {
        std::cout << "Loi: khong tim thay sach co id " << bookId << "!" << std::endl;
        return false;
    }

    book->setTitle(title);
    book->setAuthor(author);
    book->setCategory(category);
    book->setTotalCopies(totalCopies);
    return true;
}

Book* Library::findBookById(const std::string& bookId) {
    for (size_t i = 0; i < books.size(); i++) {
        if (bookId == books[i].getBookId()) return &books[i];
    }
    return nullptr;
}

std::vector<Book> Library::getAllBooks() const {
    return books;
}

std::vector<Book> Library::getAvailableBooks() const {
    std::vector<Book> availableBooks;
    for (const Book& b : books) {
        if (b.getAvailableCopies() > 0) availableBooks.push_back(b);
    }
    return availableBooks;
}