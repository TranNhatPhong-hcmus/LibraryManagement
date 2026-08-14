#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;

public:
    UserManager();

    void addUser(const User& user);
    bool removeUser(const std::string& userId);
    bool updateUser(const std::string& userId, const std::string& name, const std::string& email);

    User* findUserById(const std::string& userId);

    std::vector<User> getAllUsers() const;
};

#endif