#ifndef BOOK_H
#define BOOK_H


#include <string>

class Book {
private:
    std::string bookId;
    std::string title;
    std::string author;
    std::string category;
    int totalCopies;
    int availableCopies;
public:
    Book(const std::string& bookId, const std::string& title, const std::string& author,
        const std::string& category, int totalCopies);

    const std::string& getBookId() const { return bookId; }
    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getCategory() const { return category; }
    int getTotalCopies() const { return totalCopies; }
    int getAvailableCopies() const { return availableCopies; }

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setCategory(const std::string& category);
    void setTotalCopies(int totalCopies);

    bool isAvailable() const { return (availableCopies > 0); }

    bool decreaseAvailable();
    bool increaseAvailable();
};

#endif