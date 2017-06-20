//
// Created by Lanh Huynh on 21/05/2017
//
#ifndef ASSIGNMENT2_ACCOUNT_H
#define ASSIGNMENT2_ACCOUNT_H


#include "User.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <string>
#include <iostream>
#include <fstream>


const size_t USN_SIZE = 30;
const size_t PWD_SIZE = 30;
const size_t ROLE_SIZE = 4;
const size_t MAX_RENT2 = 100;

enum { A_U_NORMAL = 1 , A_U_WAIT_VERIFY = 2, A_U_LOCK = 3};

class Account
{
public:
    Account(long lid = 0, long aid = 0, std::string usn = "", std::string pwd = "", std::string role ="100", int st = 0);
    void setUserName(std::string);              // Gán tên đăng nhập
    void setPassword(std::string);              // Gán mật khẩu
    void setState(int);                         // Gán trạng thái
    void setLibID(long);                        // Gán mã số thư viện
    void setAccountID(long);                    // Gán mã số tài khoản
    long getLibID() const;                      // Trả về mã số thư viện
    long getAccountID() const;                  // Trả về mã số tài khoản
    std::string getUserName() const;            // Trả về tên đăng nhập
    std::string getPassword() const;            // Trả về mật khẩu
    int getState() const;                       // Trả về trạng thái
    void setRole(std::string);                  // Gán vai trò
    std::string getRole() const;                // Trả về vai trò
    void setNumRent(long );                     // Gán số lượng sách đang mượn
    long getNumRent() const;                    // Trả về số lượng sách đang mượn
    void setRentList(long [MAX_RENT2]);         // Gán danh sách sách đang mượn
    long* getRentList();                        // Trả về danh sách sách đang mượn

    void readData(long);                        // Đọc thông tini từ mã số tài khoản
    void saveData();                            // Lưu thông tin xuống file
    void saveData(long);                        // Lưu thông tin xuống file

    void addRentRecord(long);                   // Thêm sách vào danh sách mượn
    //void returnBook(long);                      // Xóa sách ttrong danh sách mượn
private:

    long libID;                                 // Mã số thư viện
    long accountID;                             // Mã số tài khoản
    char userName[USN_SIZE];                    // Tên đăng nhập
    char password[PWD_SIZE];                    // Mật khẩu
    char userRole[ROLE_SIZE];                   // Vai trò - 1 hoặc 0
    int numRent;                                // Số lượng sách mượn
    long rentList[MAX_RENT2];
    int state;
};
#endif // !ASSIGNMENT2_ACCOUNT_H
