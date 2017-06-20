#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H

#include <QStackedWidget>
#include <string>
#include <QMessageBox>
#include <QDialog>
#include <QWidget>
#include <QDebug>
#include "Reader.h"
#include "Librarian.h"
#include "UserManager.h"
#include "Account.h"
#include "User.h"
#include "Notification.h"
namespace Ui {
class StartProgram;
}

class StartProgram : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StartProgram(QWidget *parent = 0);
    ~StartProgram();
     static void resetProg();
private slots:
    void userLogin();           // Đăng nhập
    void enableLoginButton();   // Xác thực lúc đăng nhập
    void loginRole();           // Lựa chọn vai trò lúc đăng nhập
    void saveData();            // Lưu dữ liệu khi chọn chức năng đăng kí

    void enableSignUp();        // Xác thực lúc đăng kí tài khoản

    void signup_verify();       // Xác thực khi đăng kí
    void signup_verify_2();     // Xác thực khi đăng kí

    void reset();


private:
    Account tempAccount;        // Tài khoản tạm lúc đăng nhập/ đăng kí
    User tempUser;              // Người dùng tạm để xác thực thông tin lúc đăng kí/ đăng nhập
    Ui::StartProgram *ui;
};

#endif // STARTPROGRAM_H
