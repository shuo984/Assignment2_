#ifndef ASSIGNMENT2_GUEST_H
#define ASSIGNMENT2_GUEST_H

#include "User.h"
#include <string>
#include <iostream>

class Guest
{
public:
    Guest(long = 0, std::string = "");
    int regAccount();
    void setName(std::string);
    void setUserID(long);
    std::string getFullName() const;
    long getUserID() const;
private:
    long userID;
    char fullName[NAME_SIZE];

};
#endif // !ASSIGNMENT2_GUEST_H

