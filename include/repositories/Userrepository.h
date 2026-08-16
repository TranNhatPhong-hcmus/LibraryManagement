#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <vector>
#include <string>
#include "User.h"

class UserRepository {
private:
    std::string filePath;

public:
    UserRepository(const std::string& filePath);

    std::vector<User> loadUsers();
    bool saveUsers(const std::vector<User>& users);
};

#endif