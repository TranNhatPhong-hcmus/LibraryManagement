#include "UserRepository.h"
#include "StringUtils.h"
#include <fstream>
#include <iostream>

UserRepository::UserRepository(const std::string& filePath) : filePath(filePath) {}

std::vector<User> UserRepository::loadUsers() {
    std::vector<User> users;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de doc!" << std::endl;
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> parts = split(line, '|');
        if (parts.size() != 4) {
            std::cout << "Loi: dong du lieu khong hop le, bo qua: " << line << std::endl;
            continue;
        }

        std::string userId = parts[0];
        std::string name = parts[1];
        UserRole role = stringToUserRole(parts[2]);
        std::string email = parts[3];

        users.push_back(User(userId, name, role, email));
    }

    file.close();
    return users;
}

bool UserRepository::saveUsers(const std::vector<User>& users) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Loi: khong mo duoc file " << filePath << " de ghi!" << std::endl;
        return false;
    }

    for (size_t i = 0; i < users.size(); i++) {
        file << users[i].getUserId() << "|"
            << users[i].getName() << "|"
            << userRoleToString(users[i].getRole()) << "|"
            << users[i].getEmail() << "\n";
    }

    file.close();
    return true;
}