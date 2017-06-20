#include "loginform.h"
#include "ui_loginform.h"
#include "selectrole.h"

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm),
    roleUi(new Ui::SelectRole)
{
    ui->setupUi(this);
    setWindowTitle(tr("Login"));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->loginNotif->setVisible(false);
    connect(ui->loginButton, SIGNAL(clicked(bool)),this, SLOT(userLogin()));
    connect(ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(loginNotification()));

}

LoginForm::~LoginForm()
{
    delete ui;
}
void LoginForm::userLogin()
{
    std::string userName = ui->usernameLine->text().toStdString();
    std::string password = ui->passwordLine->text().toStdString();
    bool isLogin = false;
    Account tempAccount;
    for (int i = 0 ; i < User::getFAccount() && !isLogin; ++i)
    {
        tempAccount.readData(i+1);
        if (tempAccount.getUserName() == userName && tempAccount.getPassword() == password)
            isLogin = true;
    }
    User tempUser;
    tempUser.readUser(tempAccount.getLibID());
    if (!isLogin)
    {
        ui->loginNotif->setText("Login fail, please try again!");
        ui->loginNotif->setVisible(true);
    }
    else if (tempAccount.getState() && tempUser.getState())
    {
        ui->loginNotif->setVisible(false);
        this->close();
        SelectRole *sel = new SelectRole;
        sel->enableButton(tempAccount.getRole());
        sel->show();
    }



}
void LoginForm::loginNotification()
{
    //ui->loginNotif->setVisible(false);
}
