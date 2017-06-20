#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <QDebug>
#include <vector>
#include "User.h"

class StartProgram;

namespace Ui {
class UserManager;
}

class UserManager : public QMainWindow, public User
{
    Q_OBJECT

public:
    explicit UserManager(const User& ={}, QWidget *parent = 0);
    ~UserManager();
    void setInfo(long);                     // Gán thông tin người dùng lúc đăng nhập vào chương trình
private slots:
    void addUser_connect();                     // Kết nối tín hiệu cần thiết để thêm người dùng
    void enableAddUser();                       // Xác thực khi thêm người dung
    void addUser_save();                        // Lưu thông tin xuống file khi hoàn tất chương trình
    void addUser_clear();                       // Xóa thông tin cũ trên các hàng, ẩn thông báo,..

    void searchAccount_search();                // Tìm kiếm khi người dùng nhấn nút tìm kiếm

    void editUser_search(long);                   // Tìm kiếm người dùng trước khi bắt đầu sửa
    void editUser_save();                       // Lưu thông tin xuôngs file sau khi sửa xong
    void editUser_editAccount(QString);         // Sửa tài khoản của người dùng
    void editUser_saveAccount();                // Lưu tài khoản sau khi sửa xong xuống file
    void editUser_clear();                      // Xóa thông tin cũ trên dòng nhập, ẩn thông báo,..
    void editUser_verify();                     // Xác thực lúc sửa thông tin
    void editUser_verify_2();                   // Xác thực lúc sửa thông tin
    void editUser_deleteU();                    // Xóa người dùng khỏi hệ thống
    void editUser_deleteA(int);                 // Xóa Tài khoản
    void editUser_connect();                    // Kết nối các tín hiệu cần thiết cho chức năng sửa thông tin

    void addAccount_connect();                  // Kết nối tín hiệu cần thiết để thêm tài khoản


    void changePW_connect();                    // Đổi mật khẩu người dùng khác: kết nối tín hiệu cần thiết



    void changePW_find();                       // Tìm kiếm tài khoản cần đổi trước
    void changePW_save();                       // Lưu thông tin khi xong chức năng
    void changePW_clear();                      // Xóa dữ liệu cũ trên dòng nhập, khóa nút, ẩn label,...
    void changePW_verify();                     // Xác thực lúc đổi mật khẩu



    void searchUser_search();                   // Tìm kiếm người dùng
    void searchUser_connect();                  // Kết nối tín hiệu cần thiết


    void addAccount_beg();                      // Thêm tài khoản mới cho người dùng
    void addAccount_clear();                    // Xóa thông itn cũ, ẩn label
    void addAccount_save();                     // Lưu thông tin khi xong
    void addAccount_verify();                   // Xác thực thông tin khi đổi



    void verifySignup();                        // Xác thực đăng kí
    void verifySignup_accept_i(long);           // Chấp nhận đăng kí
    void verifySignup_cancel_i(long);           // Từ chối đăng kí

    void info_save();                           // Lưu thông tin người dùng hiện tại
    void logout();                              // Đăng xuất
private:
    Ui::UserManager *ui;
    long tempUID;
    long tempAID;
};

#endif // USERMANAGER_H
