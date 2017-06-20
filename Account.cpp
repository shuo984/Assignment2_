#include "Account.h"
using namespace std;
Account::Account(long lid, long aid, string usn, string pwd, string role, int st)
    :libID(lid),accountID(aid),numRent(0),state(st)
{
    setUserName(usn);
    setPassword(pwd);
    setRole(role);
}
void Account::setUserName(string usn)
{
    int size = usn.size() < USN_SIZE ? usn.size() : USN_SIZE - 1;
    usn.copy(userName, size);
    userName[size] = '\0';
}
void Account::setPassword(string pwd)
{
    int size = pwd.size() < PWD_SIZE ? pwd.size() : PWD_SIZE - 1;
    pwd.copy(password, size);
    password[size] = '\0';
}
void Account::setState(int st)
{
    state = st;
}
void Account::setLibID(long lid)
{
    libID = lid;
}
void Account::setAccountID(long aid)
{
    accountID = aid;
}
long Account::getLibID() const
{
    return libID;
}
long Account::getAccountID() const
{
    return accountID;
}
std::string Account::getUserName() const
{
    return userName;
}
std::string Account::getPassword() const
{
    return password;
}
int Account::getState() const
{
    return state;
}
void Account::readData(long id)
{
    fstream dataFin("account_data.txt");
    if (!dataFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    dataFin.seekg((id - 1) * sizeof(Account));
    dataFin.read(reinterpret_cast<char*>(this), sizeof(Account));
    dataFin.close();

}
void Account::saveData()
{
    saveData(getAccountID());
}
void Account::saveData(long id)
{
    fstream dataFout("account_data.txt");
    if (!dataFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    dataFout.seekp((id - 1) * sizeof(Account));
    dataFout.write(reinterpret_cast<char*>(this), sizeof(Account));
    dataFout.close();
}

void Account::setRole(string role)
{
    int size = role.size() < ROLE_SIZE ? role.size() : ROLE_SIZE - 1;
    role.copy(userRole, size);
    userRole[size] = '\0';
}
string Account::getRole() const
{
    return userRole;
}
void Account::setNumRent(long numR)
{
    numRent = numR;
}
long Account::getNumRent() const
{
    return numRent;
}
void Account::setRentList(long rList[MAX_RENT2])
{
    for (int i = 0; i < getNumRent(); ++i)
        rentList[i] = rList[i];
}
long* Account::getRentList()
{
    return rentList;
}

void Account::addRentRecord(long id)
{
    rentList[numRent++] = id;
}

