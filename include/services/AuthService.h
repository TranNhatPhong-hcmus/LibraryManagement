#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include "UserManager.h"
#include "Admin.h"

class AuthService {
private:
    UserManager& userManager;
    Admin& admin;

public:
    AuthService(UserManager& userManager, Admin& admin);

    User* loginUser(const std::string& userId);
    bool loginAdmin(const std::string& adminId, const std::string& password);
};

#endif