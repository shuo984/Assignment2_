#ifndef SOURCE_CPP
#define SOURCE_CPP

#include "User.h"
#include "Account.h"
#include "BookType.h"
#include "Date.h"
#include "Guest.h"
#include "Librarian.h"
#include "Reader.h"
#include "RentBook.h"
#include "UserManager.h"
using namespace std;

void resetProg()
{
    BookType blankBook;
    User blankUser;
    Account blankAccount;
    RentBook blankRent;
    ofstream bookFout("book_data.txt");
    bookFout.seekp(0);
    ofstream accFout("account_data.txt");
    accFout.seekp(0);
    ofstream userFout("user_data.txt");
    userFout.seekp(0);
    ofstream taccFout("account_temp.txt");
    taccFout.seekp(0);
    ofstream tuserFout("user_temp.txt");
    tuserFout.seekp(0);
    ofstream rentFout("rent_data.txt");
    rentFout.seekp(0);
    for (int i = 0; i < 10000; ++i)
    {
        bookFout.write(reinterpret_cast<char*>(&blankBook), sizeof(BookType));
        accFout.write(reinterpret_cast<char*>(&blankAccount), sizeof(Account));
        userFout.write(reinterpret_cast<char*>(&blankUser), sizeof(User));
        rentFout.write(reinterpret_cast<char*>(&blankRent), sizeof(RentBook));
        taccFout.write(reinterpret_cast<char*>(&blankAccount), sizeof(Account));
        tuserFout.write(reinterpret_cast<char*>(&blankUser), sizeof(User));
    }
    ofstream resParam("foo.txt");

    // Hang 1: So luong sach
    // Hang 2: So luong nguoi dung
    // Hang 3: So luong tai khoan
    // Hang 4: So luong ban ghi muon
    // Hang 5: So luong ban ghi da luu tru ( Da tra )
    // Hang 6: So luong thong bao da gui

    resParam << "NumBook:" << "\t\t" << 0 << endl;
    resParam << "NumUser: " << "\t\t"  << 1 << endl;
    resParam << "NumAccount: " << "\t\t"  << 1 << endl;
    resParam << "NumRent: " << "\t\t"  << 0 << endl;
    resParam << "NumNotif: " << "\t\t"  << 0 << endl;
    User adminUser(1,1,1,"Huỳnh Văn Lành","20/12/1998","Sinh Viên","lanhhv84@gmail.com",A_U_NORMAL);
    Account adminAcc(1,1,"admin","admin","111",true);
    adminUser.addMoreAccount(1);
    adminUser.saveUser();
    adminAcc.saveData();

    remove("param_data.txt");
    resParam.close();
    rename("foo.txt", "param_data.txt");
}

#endif
