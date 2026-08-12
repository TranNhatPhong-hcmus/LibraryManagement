#include "Book.h"
#include <iostream>
#include <string>

Book::Book(const std::string& bookId, const std::string& title, const std::string& author,
    const std::string& category, int totalCopies)
    : bookId(bookId), title(title), author(author),
    category(category), totalCopies(totalCopies), availableCopies(totalCopies) {
}

void Book::setTitle(const std::string& title) {
    if (title.empty()) {
        std::cout << "Loi: ten sach khong duoc trong!";
        return;
    }
    this->title = title;
}

void Book::setAuthor(const std::string& author) {
    if (author.empty()) {
        std::cout << "Loi: ten tac gia khong duoc trong!";
        return;
    }
    this->author = author;
}

void Book::setCategory(const std::string& category) {
    if (category.empty()) {
        std::cout << "Loi: the loai khong duoc trong!";
        return;
    }
    this->category = category;
}

void Book::setTotalCopies(int totalCopies) {
    if (totalCopies < 0) {
        std::cout << "Loi: tong so sach khong duoc be hon khong!" << std::endl;
        return;
    }

    int borrowedCount = this->totalCopies - this->availableCopies;  // số cuốn đang được mượn
    if (totalCopies < borrowedCount) {
        std::cout << "Loi: khong the giam tong so sach xuong thap hon so cuon dang duoc muon ("
            << borrowedCount << ")!" << std::endl;
        return;
    }

    int diff = totalCopies - this->totalCopies;
    this->totalCopies = totalCopies;
    this->availableCopies += diff;
}

bool Book::decreaseAvailable() {
    if (!isAvailable()) {
        std::cout << "Loi: khong con sach! ";
        return false;
    }
    availableCopies--;
    return true;
}

bool Book::increaseAvailable() {
    if (availableCopies >= totalCopies) {
        std::cout << "Loi: khong the tra them, da du tong so sach!" << std::endl;
        return false;
    }
    availableCopies++;
    return true;
}