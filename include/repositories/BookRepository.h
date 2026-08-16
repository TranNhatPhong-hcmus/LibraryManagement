#ifndef BOOK_REPOSITORY_H
#define BOOK_REPOSITORY_H

#include <vector>
#include <string>
#include "Book.h"

class BookRepository {
private:
    std::string filePath;

public:
    BookRepository(const std::string& filePath);

    std::vector<Book> loadBooks();
    bool saveBooks(const std::vector<Book>& books);
};

#endif