#include "UserManager.h"
#include <string>
#include <vector>
#include <iostream>

UserManager::UserManager() {}

void UserManager::addUser(const User& user) {
    if (findUserById(user.getUserId())) {
        std::cout << "Loi : user da ton tai!" << std::endl;
        return;
    }
    users.push_back(user);
}

bool UserManager::removeUser(const std::string& userId) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUserId() == userId) {
            users.erase(users.begin() + i);
            return true;
        }
    }
    return false;
}

bool UserManager::updateUser(const std::string& userId, const std::string& name, const std::string& email) {
    User* user = findUserById(userId);
    if (!user) {
        std::cout << "Loi: khong tim thay user co id " << userId << "!" << std::endl;
        return false;
    }
    user->setName(name);
    user->setEmail(email);
    return true;
}

User* UserManager::findUserById(const std::string& userId) {
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getUserId() == userId) return &users[i];
    }
    return nullptr;
}

std::vector<User> UserManager::getAllUsers() const {
    return users;
}