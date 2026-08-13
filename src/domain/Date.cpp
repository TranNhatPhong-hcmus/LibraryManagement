#include "Date.h"
#include <iostream>
#include <string>
#include <sstream>

int Date::daysInMonth[][13] = { {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                                {-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} };

bool Date::isLeapYear(int nam) {
    return (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0));
}

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

std::string Date::toString() const {
    std::string date = std::to_string(day) + '/' + std::to_string(month) + '/' + std::to_string(year);
    return date;
}

Date Date::fromString(const std::string& str) {
    int dayPart = stoi(str.substr(0, str.find('/')));
    int monthPart = stoi(str.substr(str.find('/') + 1, str.find('/', str.find('/') + 1) - str.find('/') - 1));
    int yearPart = stoi(str.substr(str.find('/', str.find('/') + 1) + 1));

    Date d(dayPart, monthPart, yearPart);
    if (!d.isValid()) {
        std::cout << "Loi: ngay khong hop le: " << str << std::endl;
    }
    return d;
}

bool Date::isValid() const {
    if (month < 1 || month > 12) return false;
    if (year < 0) return false;
    return day >= 1 && day <= daysInMonth[isLeapYear(year)][month];
}

bool Date::operator>(const Date& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.year;
    return day > other.day;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator<(const Date& other) const {
    return other > *this;
}