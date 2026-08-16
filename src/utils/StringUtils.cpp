#include "StringUtils.h"
#include <sstream>

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
}