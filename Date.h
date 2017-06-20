#ifndef ASSIGNMENT2_DATE_H
#define ASSIGNMENT2_DATE_H

#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <array>

// Don gian

class Date
{
    friend std::ostream &operator<<(std::ostream&, Date);
public:
    Date(int = 1, int = 1, int = 1970);
    int operator-(Date);
    Date operator+(int);
    Date setDay(int);
    Date setMonth(int);
    Date setYear(int);
    int getDay();
    int getMonth();
    int getYear();
    Date getCurrentDate();
    void printDate();
private:
    bool leapYear(int);
    int day;
    int month;
    int year;
};
#endif // !ASSIGNMENT2_DATE_H

