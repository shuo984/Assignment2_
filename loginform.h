#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QLayout>
#include <QDebug>
#include <string>
#include "User.h"
#include "Account.h"
#include "ui_selectrole.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
private slots:
    void userLogin();
    void loginNotification();
private:
    Ui::LoginForm *ui;
    Ui::SelectRole *roleUi;
};

#endif // LOGINFORM_H
