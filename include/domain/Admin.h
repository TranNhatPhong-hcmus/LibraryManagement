#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
private:
    std::string adminId;
    std::string name;
    std::string password;

public:
    Admin(const std::string& adminId, const std::string& name, const std::string& password);

    const std::string& getAdminId() const { return adminId; }
    const std::string& getName() const { return name; }

    bool checkPassword(const std::string& password) const;
};


#endif