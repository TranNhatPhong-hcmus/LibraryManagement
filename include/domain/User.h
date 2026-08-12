#ifndef USER_H
#define USER_H

#include <string>

enum class UserRole { Student, Teacher };

class User {
private:
    std::string userId;
    std::string name;
    UserRole role;
    std::string email;
public:
    User(const std::string& userId, const std::string& name, UserRole role, const std::string& email);

    const std::string& getUserId() const { return userId; }
    const std::string& getName() const { return name; }
    UserRole getRole() const { return role; }
    const std::string& getEmail() const { return email; }

    void setName(const std::string& name);
    void setEmail(const std::string& email);
};

#endif