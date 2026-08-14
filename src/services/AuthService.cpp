#include "AuthService.h"
#include "UserManager.h"
#include <string>
#include <iostream>

AuthService::AuthService(UserManager& userManager) : userManager(userManager) {}

User* AuthService::loginUser(const std::string& userId) {
    User* user = userManager.findUserById(userId);
    if (!user) {
        std::cout << "khong tim thay user!" << std::endl;
        return nullptr;
    }
    std::cout << "Xin chao, " << user->getName() << std::endl;
    return user;
}

