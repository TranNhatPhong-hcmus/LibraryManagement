#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day, month, year;
    static bool isLeapYear(int nam);
    static int daysInMonth[][13];
public:
    Date(int day, int month, int year);

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    std::string toString() const;
    static Date fromString(const std::string& str);

    bool isValid() const;

    bool operator>(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
};


#endif