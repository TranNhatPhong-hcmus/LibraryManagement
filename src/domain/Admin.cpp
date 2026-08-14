#include "Admin.h"
#include <string>

Admin::Admin(const std::string& adminId, const std::string& name, const std::string& password) :
    adminId(adminId), name(name), password(password) {
}

bool Admin::checkPassword(const std::string& password) const {
    return this->password == password;
}