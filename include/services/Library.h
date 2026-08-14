#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "Book.h"

class Library {
private:
    std::vector<Book>  books;
public:
    Library();

    void addBook(const Book& book);
    bool removeBook(const std::string& bookId);
    bool updateBook(const std::string& bookId, const std::string& title, const std::string& author,
        const std::string& category, int totalCopies);

    Book* findBookById(const std::string& bookId);

    std::vector<Book> getAllBooks() const;
    std::vector<Book> getAvailableBooks() const;
};

#endif