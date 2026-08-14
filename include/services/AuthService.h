#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include "UserManager.h"

class AuthService {
private:
    UserManager& userManager;

public:
    AuthService(UserManager& userManager);

    User* loginUser(const std::string& userId);
};

#endif