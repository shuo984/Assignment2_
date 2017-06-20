#include "Date.h"
using namespace std;
Date::Date(int d, int m, int y)
{

}
int Date::getMonth()
{
    return month;
}
int Date::getDay()
{
    return day;
}
int Date::getYear()
{
    return year;
}
Date Date::setDay(int d)
{
    array<int, 12> dayM = { 31,(leapYear(getYear()) ? 29 : 28),31,30,31,30,31,31,30,31,30,31 };
    if (getMonth() <= 12 && month >= 1)
    {
        if (d > dayM[getMonth() - 1] || d < 1)
            day = 1;
        else day = d;
        day = d;
    }

    else { month = 1; day = 1; }
    return *this;
}

Date Date::setMonth(int m)
{
    if (month > 12 || month < 1)
        month = 1;
    else month = m;
    return *this;
}
Date Date::setYear(int y)
{
    year = y;
    return *this;
}
bool Date::leapYear(int y)
{
    if (y % 4 != 0)
        return false;
    if (y % 100 == 0)
        return true;
    return false;
}
Date Date::getCurrentDate()
{
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return Date(now->tm_mday, now->tm_mday, now->tm_year + 1900);
}
void Date::printDate()
{
    cout << setw(2) << setfill('0') << getDay() << '/' << setw(2) << setfill('0')
        << getMonth() << '/' << setw(4) << setfill('0') << getYear() << endl;
}
int Date::operator-(Date x)
{
    // Hoi ngu cho nay
    int dayM1[12] = { 31,(leapYear(getYear()) ? 29 : 28),31,30,31,30,31,31,30,31,30,31 };
    int dayM2[12] = { 31,(leapYear(x.getYear()) ? 29 : 28),31,30,31,30,31,31,30,31,30,31 };
    int day1 = getDay() + 365 * getYear();
    for (int i = 0; i < getMonth() - 1; ++i)
        day1 += dayM1[i];
    int day2 = getDay() + 365 * getYear();
    for (int i = 0; i < x.getMonth() - 1; ++i)
        day2 += dayM2[i];
    int ans = day2 - day1;
    for (int i = getYear(); i < x.getYear(); ++i)
        if (leapYear(i))
            ++ans;
    return ans;
}
