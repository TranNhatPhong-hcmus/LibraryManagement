#include "AuthService.h"
#include "UserManager.h"
#include "Admin.h"
#include <string>
#include <iostream>

AuthService::AuthService(UserManager& userManager, Admin& admin) : userManager(userManager), admin(admin) {}

User* AuthService::loginUser(const std::string& userId) {
    User* user = userManager.findUserById(userId);
    if (!user) {
        std::cout << "khong tim thay user!" << std::endl;
        return nullptr;
    }
    std::cout << "Xin chao, " << user->getName() << std::endl;
    return user;
}


bool AuthService::loginAdmin(const std::string& adminId, const std::string& password) {
    if (adminId == admin.getAdminId() && admin.checkPassword(password)) {
        std::cout << "Xin chao, admin " << admin.getName() << std::endl;
        return true;
    }
    return false;
}
