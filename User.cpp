#include "User.h"
using namespace std;

User::User(long lid, long uid , long pid , string name, string dob , string job , string mail ,
        long listA[NUM_ACCOUNT], int numA, int st)
    :libID(lid), userID(uid), PID(pid), numAccount(numA), state(st)
{
    setFullName(name);
    setDayOfB(dob);
    setJob(job);
    setMailAddr(mail);
    setAccountList(listA);
}
enum {NBOOKTYPE =1 , NUSER = 2 , NACCOUNT = 3, NRENT = 4, NNOTIF = 5, NTEMPACC = 6, NTEMPUSER =7 , NBOOK = 8, NUMLINE =9};

User::User(long lid, long uid, long pid, string name, string dob, string job, string mail
    , int st)
    :libID(lid), userID(uid), PID(pid),numAccount(0), state(st)
{
    setFullName(name);
    setDayOfB(dob);
    setJob(job);
    setMailAddr(mail);

}
void User::setLibID(long lid)
{
    libID = lid;
}
void User::setUserID(long uid)
{
    userID = uid;
}
void User::setPID(long pid)
{
    PID = pid;
}
void User::setFullName(string full)
{
    int size = full.size() < NAME_SIZE ? full.size() : NAME_SIZE - 1;
    full.copy(fullName, size);
    fullName[size] = '\0';
}
void User::setDayOfB(string dob)
{
    int size = dob.size() < DOB_SIZE ? dob.size() : DOB_SIZE - 1;
    dob.copy(dayOfBirth, size);
    dayOfBirth[size] = '\0';

}
void User::setJob(string job)
{
    int size = job.size() < JOB_SIZE ? job.size() : JOB_SIZE - 1;
    job.copy(userJob, size);
    userJob[size] = '\0';
}
void User::setMailAddr(string mail)
{
    int size = mail.size() < MAIL_SIZE ? mail.size() : MAIL_SIZE - 1;
    mail.copy(mailAddr, size);
    mailAddr[size] = '\0';
}
void User::setAccountList(long listA[NUM_ACCOUNT])
{
    for (int i = 0; i < numAccount; ++i)
        listAccount[i] = listA[i];
}
void User::setNumAccount(long numA)
{
    numAccount = numA;
}
void User::setState(int st)
{
    state = st;
}
long User::getLibID() const
{
    return libID;
}
long User::getUserID() const
{
    return userID;
}
long User::getUserPID() const
{
    return PID;
}
string User::getFullName() const
{
    return fullName;
}
string User::getDOB() const
{
    return dayOfBirth;
}
string User::getMailAddr() const
{
    return mailAddr;
}
long* User::getAccountList()
{
    return listAccount;
}
long User::getNumAccount() const
{
    return numAccount;
}
int User::getState() const
{
    return state;
}
void User::setNBookType(long numB)
{
    setParam(numB,NBOOKTYPE);
}
long User::getNBookType()
{
    return getParam(NBOOKTYPE);
}
void User::setNumUser(long numB)
{
    setParam(numB, NUSER);
}
long User::getNumUser()
{
    return getParam(NUSER);
}
string User::getJob() const
{
    return userJob;
}
void User::setFAccount(long numB)
{
   setParam(numB,NACCOUNT);
}
long User::getFAccount()
{
    return getParam(NACCOUNT);
}
void User::readUser(long id)
{
    fstream dataFin("user_data.txt");
    if (!dataFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    dataFin.seekg((id - 1) * sizeof(User));
    dataFin.read(reinterpret_cast<char*>(this), sizeof(User));
    dataFin.close();
}
void User::saveUser()
{
    fstream dataFout("user_data.txt");
    if (!dataFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    dataFout.seekg((getLibID() - 1) * sizeof(User));
    dataFout.write(reinterpret_cast<char*>(this), sizeof(User));
    dataFout.close();
}
void User::saveUser(long id)
{
    fstream dataFout("user_data.txt");
    if (!dataFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    dataFout.seekg((id - 1) * sizeof(User));
    dataFout.write(reinterpret_cast<char*>(this), sizeof(User));
    dataFout.close();
}

void User::setFNumRent(long numR)
{
    setParam(numR, NRENT);
}
long User::getFNumRent()
{
    return getParam(NRENT);
}

void User::addMoreAccount(long id)
{
    listAccount[getNumAccount()] = id;
    ++numAccount;
}
void User::setNNotif(long num)
{
    setParam(num, NNOTIF);
}

long User::getNNotif()
{
    return getParam(NNOTIF);
}

long User::getParam(int pos)
{

    fstream paramFin("param_data.txt");
    if (!paramFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    string temp;
    long value;
    for (int i = 1 ; i <= pos ; ++i)
    {
        paramFin >> temp >> value;
        paramFin.ignore();
    }
    return value;
}
void User::setParam(long value, int pos)
{
    fstream paramFin("param_data.txt");
    if (!paramFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    ofstream paramFout("foo.txt");
    if (!paramFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    string temp;
    long val;
    for (int i = 1 ; i < pos  ; ++i)
    {
        paramFin >> temp >> val;
        paramFin.ignore();
        paramFout << temp << "\t\t" << val << endl;
    }

    paramFin >> temp >> val;
    paramFin.ignore();
    paramFout << temp << "\t\t" << value << endl;
    for (int i = pos +1 ; i < NUMLINE ; ++i)
    {
        paramFin >> temp >> val;
        paramFin.ignore();
        paramFout << temp << "\t\t" << val << endl;
    }
    paramFin.close();
    paramFout.close();
    remove("param_data.txt");
    rename("foo.txt", "param_data.txt");
}


QString User::QDateToString(const QDate& date)
{
    QString ans;
    ans = (QString::number(date.day()).size() == 1 ? "0" + QString::number(date.day()) : QString::number(date.day())) + "/"
            + (QString::number(date.month()).size() == 1 ? "0" + QString::number(date.month()) : QString::number(date.month())) + "/"
            + QString::number(date.year());
    return ans;
}
QDate User::stringToQDate(QString date)
{
    replace(date.begin(), date.end(),'/',' ');
    stringstream dateStr(date.toStdString());
    int day;
    int month;
    int year;
    dateStr >> day >> month >> year;
    return QDate(day,month,year);
}
bool User::Search(string dest , string findKey)			//New function
{
    stringstream love(findKey);
    string temp;

    while (love >> temp)
        if (dest.find(temp) == std::string::npos)
            return false;
    return true;
}

void User::deleteUser(int pos)
{
    --numAccount;
    for (int i = pos +1 ; i < NUM_ACCOUNT ;++i)
        listAccount[i - 1] = listAccount[i];
    saveUser();
}

void User::setNBook(long num)
{
    setParam(num,NBOOK);
}

long User::getNBook()
{
    return getParam(NBOOK);
}
