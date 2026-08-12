#include "User.h"
#include <iostream>
#include <string>

User::User(const std::string& userId, const std::string& name, UserRole role, const std::string& email)
    : userId(userId), name(name), role(role), email(email) {
}

void User::setName(const std::string& name) {
    if (name.empty()) {
        std::cout << "Loi: ten khong duoc trong!" << std::endl;
        return;
    }
    this->name = name;
}

void User::setEmail(const std::string& email) {
    if (email.empty()) {
        std::cout << "Loi: email khong duoc trong!" << std::endl;
        return;
    }
    this->email = email;
}