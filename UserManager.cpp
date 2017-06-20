#include "UserManager.h"
#include "ui_UserManager.h"

#include "StartProgram.h"

// Add user use index 1 2
// Edit user use index 3, 4
// Delete user use index 5 6
// Lock user use index 7 8
// Reset user use index 9 10
// Find user use index 11 12
// Index 13 for edit account

// Next version:
// - Enable verify any QEditLine ( QRegExp )
// - Verify in Edit user menu
// - Enhance string search algorithm in searching for user

enum {U_ADD_USER =1, U_EDIT_USER = 2 , U_DELETE = 3,
      U_ADD_ACC = 4, U_RESPW = 5, U_VERIFY_SIGNUP = 6 , U_FIND = 7,
      U_EDIT_ACC = 8, U_DELETE_ACC = 9 , U_ABOUT = 10, U_INFO = 11};

UserManager::UserManager(const User& x, QWidget *parent) :
    QMainWindow(parent),
    User(x),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    ui->implementField->setCurrentIndex(0);

    // Khoửi tạo các chức năng chính

    addUser_clear();

    editUser_clear();
    changePW_clear();
    searchUser_connect();
    editUser_connect();
    addAccount_connect();
    changePW_connect();
    // Kết nối các nút lớn
    addUser_connect();
    addAccount_clear();
    addUser_connect();

    //connect(ui->addUser_backButton,  &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(0);});
    connect(ui->editUserButton,&QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_EDIT_USER);});
    connect(ui->findUserButton, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_FIND);});
    connect(ui->changePW_Button, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_RESPW);});
    connect(ui->aboutLIBPRO_button, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_ABOUT);});
    connect(ui->verifySignup_Button,&QPushButton::clicked,[=]{verifySignup();});
    connect(ui->logout_Button,&QPushButton::clicked,[=]{logout();});

    ui->verifySignupView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->findUserView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->searchAccount_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->findUser_findButton, SIGNAL(clicked(bool)), this, SLOT(searchUser_search()));

    connect(ui->info_Button, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(U_INFO);});
    connect(ui->editUser_backButton, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(U_FIND);});
    connect(ui->searchAccount_searchButton, &QPushButton::clicked, [=]{searchAccount_search();});

}
UserManager::~UserManager()
{
    delete ui;
}

// Xác thực thông tin khi theem người dùng mới
void UserManager::addUser_connect()
{
    // Xác thực khi thêm người dùng ( hơi nhiều )

    connect(ui->nameLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->dobLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->jobLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->mailLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->pwLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->userID_addUser, SIGNAL(textChanged(QString)), this,SLOT(enableAddUser()));
    connect(ui->userPID_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->usnLine_addUser, SIGNAL(textChanged(QString)), this, SLOT(enableAddUser()));
    connect(ui->readerQRButton, SIGNAL(toggled(bool)), this, SLOT(enableAddUser()));
    connect(ui->usermanagerQRButton, SIGNAL(toggled(bool)), this, SLOT(enableAddUser()));
    connect(ui->librarianQRButton, SIGNAL(toggled(bool)), this, SLOT(enableAddUser()));
    connect(ui->addUserButton, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_ADD_ACC);});
    connect(ui->addUserButton, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(U_ADD_USER);});

    connect(ui->confirmButton_addUser,SIGNAL(clicked(bool)),this, SLOT(addUser_save()));
    ui->addUser_libIDLine->setText(QString::number(getNumUser() + 1));
    ui->addUser_aLine->setText(QString::number(User::getFAccount() + 1));
    ui->adduser_succLabel->setVisible(false);
}
void UserManager::enableAddUser()
{

    bool err = false;
    bool dupEmail = false;
    bool dupUserID = false;
    bool dupUserPID = false;
    bool dupUSN = false;
    User tempU;
    Account tempA;
    for (int i = 0 ; i < User::getNumUser(); ++i)
    {
        tempU.readUser(i+1);
        if (tempU.getMailAddr() == ui->mailLine_addUser->text().toStdString())
            dupEmail=true;
        if (tempU.getUserID() == ui->userID_addUser->text().toLong())
            dupUserID = true;
        if (tempU.getUserPID() == ui->userPID_addUser->text().toLong())
            dupUserPID=true;
    }
    if (!ui->readerQRButton->isChecked() && !ui->usermanagerQRButton->isChecked() && !ui->librarianQRButton->isChecked())
        err = true;
    else
        ui->confirmButton_addUser->setEnabled(true);
    for (int i = 0 ; i < User::getFAccount() && !dupUSN ; ++i)
    {
        tempA.readData(i+1);
        if (tempA.getUserName() == ui->usnLine_addUser->text().toStdString())
        {
            dupUSN=true;
            err = true;
        }
    }
    if (ui->nameLine_addUser->text().isEmpty())
        err = true;
    if (ui->dobLine_addUser->text().isEmpty())
        err = true;
    if (ui->jobLine_addUser->text().isEmpty())
        err = true;
    if (!ui->mailLine_addUser->text().isEmpty())
    {
        if (dupEmail)
        {
            ui->mailErrLabel_addUser->setVisible(true);
            err = true;
        }
        else
            ui->mailErrLabel_addUser->setVisible(false);
    }
    else
    {
        ui->mailErrLabel_addUser->setVisible(true);
        err = true;
    }
    if (ui->pwLine_addUser->text().isEmpty())
        err = true;

    if (ui->userID_addUser->text().isEmpty())
    {
            err = true;
            ui->userIDErrLabel_addUser->setVisible(true);
    }
    else
    {
        ui->userIDErrLabel_addUser->setVisible(false);

        for (int i = 0 ; i < getNumUser() ; ++i)
        {
            tempU.readUser(i+1);
            if (tempU.getUserID() == ui->userID_addUser->text().toLong())
                dupUserID = true;
        }
        if (dupUserID)
            ui->userIDErrLabel_addUser->setVisible(true);
        else
            ui->userIDErrLabel_addUser->setVisible(false);
    }


    if (!ui->userPID_addUser->text().isEmpty())
    {
        if (dupUserPID)
        {
            ui->userPIDErrLabel_addUser->setVisible(true);\
            err = true;
        }
        else
            ui->userPIDErrLabel_addUser->setVisible(false);
    }
    else
    {
        ui->userPIDErrLabel_addUser->setVisible(true);
        err = true;
    }
    if (!ui->usnLine_addUser->text().isEmpty())
    {
        if (dupUSN)
        {
            ui->usnErrLabel_adduser->setVisible(true);
            err = true;
        }
        else
            ui->usnErrLabel_adduser->setVisible(false);
    }
    else
    {
        ui->usnErrLabel_adduser->setVisible(true);
        err = true;
    }


    ui->confirmButton_addUser->setEnabled(!err);
}

// Lưu thông tin người dùng

void UserManager::addUser_save()
{
    long libID = User::getNumUser() +1;
    long aId = User::getFAccount() +1;
    long userID = ui->userID_addUser->text().toLong();
    long userPID =ui->userPID_addUser->text().toLong();
    std::string name = ui->nameLine_addUser->text().toStdString();
    std::string dob = ui->dobLine_addUser->text().toStdString();
    std::string job = ui->jobLine_addUser->text().toStdString();
    std::string mail = ui->mailLine_addUser->text().toStdString();
    std::string usn = ui->usnLine_addUser->text().toStdString();

    std::string pw = ui->pwLine_addUser->text().toStdString();
    int state = ui->addUser_state->currentIndex();
    std::string role = "000";
    if (ui->readerQRButton->isChecked())
        role[0] = '1';
    if (ui->librarianQRButton->isChecked())
        role[1] = '1';
    if (ui->usermanagerQRButton->isChecked())
        role[2] = '1';
    Account newAccount(libID,aId,usn,pw,role,state);
    User newUser(libID,userID, userPID,name,dob,job,mail,state);
    newUser.addMoreAccount(aId);
    newUser.saveUser();
    newAccount.saveData();
    User::setFAccount(aId);
    User::setNumUser(libID);
    ui->addUser_aLine->setText(QString::number(User::getFAccount() + 1));
    ui->adduser_succLabel->setVisible(true);
    ui->confirmButton_addUser->setEnabled(false);


    connect(ui->userID_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->userPID_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->nameLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->dobLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->jobLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->mailLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->usnLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});
    connect(ui->pwLine_addUser, &QLineEdit::textChanged,[=]{ui->adduser_succLabel->setVisible(false);});


    connect(ui->confirmButton_addUser, &QPushButton::clicked,
            [=]{ui->addUser_libIDLine->setText(QString::number(getNumUser() + 1));});

}



void UserManager::editUser_search(long i)
{
    User tempU;
    editUser_clear();

    long lid = i;
    tempU.readUser(lid);
    ui->editUser_uSeccLabel->setVisible(false);
    ui->editUser_aSuccLabel->setVisible(false);

    if (tempU.getLibID() == 0)
    {
        ui->editUser_nFoundLabel->setVisible(true);
        ui->editUser_editArea->setVisible(false);
    }
    else
    {
       ui->editUser_nameLine->setText(QString(tempU.getFullName().c_str()));
       ui->editUser_LIDLine->setText(QString::number(tempU.getLibID()));
       ui->editUser_userIDLine->setText(QString::number(tempU.getUserID()));
       ui->editUser_userPIDLine->setText(QString::number(tempU.getUserPID()));
       ui->editUser_DOBLine->setText(QString(tempU.getDOB().c_str()));
       ui->editUser_JOBLine->setText(QString(tempU.getJob().c_str()));
       ui->edituser_mailLine->setText(QString(tempU.getMailAddr().c_str()));
       ui->editUser_numALabel->setText("Số tài khoản đã đăng kí: " + QString::number(tempU.getNumAccount()));
       ui->editUser_state->setCurrentIndex(tempU.getState());
       ui->editUser_editArea->setVisible(true);
       ui->editUser_nFoundLabel->setVisible(false);
       if (tempU.getNumAccount() == 0)
       {
           ui->editUser_acc1Group_2->setVisible(false);
           ui->editUser_acc2Group_2->setVisible(false);
           ui->editUser_acc3Group_2->setVisible(false);
           ui->editUser_acc4Group_2->setVisible(false);
           ui->editUser_acc5Group_2->setVisible(false);
       }
       if (tempU.getNumAccount() == 1)
       {
           ui->editUser_acc1Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[0]));
           Account tempA;
           tempA.readData(tempU.getAccountList()[0]);
           ui->acc1_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           ui->editUser_acc1Group_2->setVisible(true);
           ui->editUser_acc2Group_2->setVisible(false);
           ui->editUser_acc3Group_2->setVisible(false);
           ui->editUser_acc4Group_2->setVisible(false);
           ui->editUser_acc5Group_2->setVisible(false);
       }
       if (tempU.getNumAccount() == 2)
       {
           ui->editUser_acc1Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[0]));
           ui->editUser_acc2Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[1]));
           Account tempA;
           tempA.readData(tempU.getAccountList()[0]);
           ui->acc1_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[1]);
           ui->acc2_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           ui->editUser_acc1Group_2->setVisible(true);
           ui->editUser_acc2Group_2->setVisible(true);
           ui->editUser_acc3Group_2->setVisible(false);
           ui->editUser_acc4Group_2->setVisible(false);
           ui->editUser_acc5Group_2->setVisible(false);
        }

       if (tempU.getNumAccount() == 3)
       {
           ui->editUser_acc1Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[0]));
           ui->editUser_acc2Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[1]));
           ui->editUser_acc3Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[2]));
           Account tempA;
           tempA.readData(tempU.getAccountList()[0]);
           ui->acc1_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[1]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[2]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           ui->editUser_acc1Group_2->setVisible(true);
           ui->editUser_acc2Group_2->setVisible(true);
           ui->editUser_acc3Group_2->setVisible(true);
           ui->editUser_acc4Group_2->setVisible(false);
           ui->editUser_acc5Group_2->setVisible(false);
       }

       if (tempU.getNumAccount() == 4)
       {
           Account tempA;
           tempA.readData(tempU.getAccountList()[0]);
           ui->acc1_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[1]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[2]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[3]);
           ui->acc4_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           ui->editUser_acc1Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[0]));
           ui->editUser_acc2Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[1]));
           ui->editUser_acc3Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[2]));
           ui->editUser_acc4Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[3]));
           ui->editUser_acc1Group_2->setVisible(true);
           ui->editUser_acc2Group_2->setVisible(true);
           ui->editUser_acc3Group_2->setVisible(true);
           ui->editUser_acc4Group_2->setVisible(true);
           ui->editUser_acc5Group_2->setVisible(false);
       }

       if (tempU.getNumAccount() == 5)
       {
           Account tempA;
           tempA.readData(tempU.getAccountList()[0]);
           ui->acc1_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[1]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[2]);
           ui->acc3_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[3]);
           ui->acc4_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           tempA.readData(tempU.getAccountList()[4]);
           ui->acc5_vLabel->setVisible(tempA.getState() == A_U_WAIT_VERIFY);
           ui->editUser_acc1Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[0]));
           ui->editUser_acc2Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[1]));
           ui->editUser_acc3Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[2]));
           ui->editUser_acc4Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[3]));
           ui->editUser_acc5Label->setText("Mã tài khoản " + QString::number(tempU.getAccountList()[4]));
           ui->editUser_acc1Group_2->setVisible(true);
           ui->editUser_acc2Group_2->setVisible(true);
           ui->editUser_acc3Group_2->setVisible(true);
           ui->editUser_acc4Group_2->setVisible(true);
           ui->editUser_acc5Group_2->setVisible(true);
       }
    }
    ui->editUser_addAButton->setEnabled(tempU.getNumAccount() < 5);
    ui->implementField->setCurrentIndex(U_EDIT_USER);
}
void UserManager::editUser_save()
{
    std::string name = ui->editUser_nameLine->text().toStdString();
    long uid = ui->editUser_userIDLine->text().toLong();
    long pid = ui->editUser_userPIDLine->text().toLong();
    std::string dob = ui->editUser_DOBLine->text().toStdString();
    std::string job = ui->editUser_JOBLine->text().toStdString();
    std::string mail = ui->edituser_mailLine->text().toStdString();
    long lid = ui->editUser_LIDLine->text().toLong();

    User tempUser;
    tempUser.readUser(lid);
    tempUser.setDayOfB(dob);
    tempUser.setJob(job);
    tempUser.setMailAddr(mail);
    tempUser.setUserID(uid);
    tempUser.setPID(pid);
    tempUser.setFullName(name);
    tempUser.setState(ui->editUser_state->currentIndex());
    tempUser.saveUser();
    ui->editUser_uSeccLabel->setVisible(true);



}
void UserManager::editUser_editAccount(QString x)
{
    long accID = x.mid(13).toLong();
    ui->implementField->setCurrentIndex(U_EDIT_ACC);
    Account tempA;
    tempA.readData(accID);

    ui->editUser_editAccount_aID->setText(QString::number(tempA.getAccountID()));
    ui->editUser_editAccount_LIBID->setText(QString::number(tempA.getLibID()));
    ui->editUser_editAccount_PW->setText(QString(tempA.getPassword().c_str()));
    ui->editUser_editAccount_USN->setText(QString(tempA.getUserName().c_str()));
    ui->editUser_editAccount_reader->setChecked(tempA.getRole()[0] == '1');
    ui->editUser_editAccount_librarian->setChecked(tempA.getRole()[1] == '1');
    ui->editUser_editAccount_usermanager->setChecked(tempA.getRole()[2] == '1');
    ui->editUser_AState->setCurrentIndex(tempA.getState());
}
void UserManager::editUser_saveAccount()
{
    long aID = ui->editUser_editAccount_aID->text().toLong();
    long lid = ui->editUser_editAccount_LIBID->text().toLong();
    std::string usn = ui->editUser_editAccount_USN->text().toStdString();
    std::string pw = ui->editUser_editAccount_PW->text().toStdString();
    std::string role = "000";
    if (ui->editUser_editAccount_reader->isChecked())
        role[0] = '1';
    if (ui->editUser_editAccount_librarian->isChecked())
        role[1] = '1';
    if (ui->editUser_editAccount_usermanager->isChecked())
        role[2] = '1';
    Account tempA(lid,aID,usn,pw,role,ui->editUser_AState->currentIndex());
    tempA.saveData();

    ui->editUser_aSuccLabel->setVisible(true);



}
void UserManager::editUser_clear()
{
    ui->editUser_editAccount_aID->clear();
    ui->editUser_editAccount_LIBID->clear();
    ui->editUser_editAccount_PW->clear();
    ui->editUser_editAccount_USN->clear();
    ui->editUser_editAccount_reader->setChecked(false);
    ui->editUser_editAccount_librarian->setChecked(false);
    ui->editUser_editAccount_usermanager->setChecked(false);
    ui->editUser_nameLine->clear();
    ui->editUser_userIDLine->clear();
    ui->editUser_userPIDLine->clear();
    ui->editUser_DOBLine->clear();
    ui->editUser_JOBLine->clear();
    ui->edituser_mailLine->clear();
    ui->editUser_LIDLine->clear();
    ui->editUser_editArea->setVisible(false);

    ui->editUser_editArea->setVisible(false);
    ui->editUser_nFoundLabel->setVisible(false);
    ui->editUser_acc1Group_2->setVisible(false);
    ui->editUser_acc2Group_2->setVisible(false);
    ui->editUser_acc3Group_2->setVisible(false);
    ui->editUser_acc4Group_2->setVisible(false);
    ui->editUser_acc5Group_2->setVisible(false);

    ui->editUser_uSeccLabel->setVisible(false);
    ui->editUser_aSuccLabel->setVisible(false);

    ui->editUser_dupEmail->setVisible(false);
    ui->editUser_dupPID->setVisible(false);
    ui->editUser_dupUID->setVisible(false);


    ui->acc1_vLabel->setVisible(false);
    ui->acc2_vLabel->setVisible(false);
    ui->acc3_vLabel->setVisible(false);
    ui->acc4_vLabel->setVisible(false);
    ui->acc5_vLabel->setVisible(false);
}
void UserManager::editUser_deleteU()
{
    long lid = ui->editUser_LIDLine->text().toLong();
    User blankU;
    Account blankA;
    User tempU;
    tempU.readUser(lid);
    for (int i = 0 ; i < tempU.getNumAccount() ; ++i)
        blankA.saveData(tempU.getAccountList()[i]);
    blankU.saveUser(lid);
    ui->implementField->setCurrentIndex(U_DELETE);
}

void UserManager::editUser_deleteA(int i)
{
    User tempU;
    Account blankA;
    tempU.readUser(ui->editUser_LIDLine->text().toLong());
    blankA.saveData(tempU.getAccountList()[i-1]);
    tempU.deleteUser(i-1);
    ui->editUser_numALabel->setText("Số tài khoản đã đăng kí: " + QString::number(tempU.getNumAccount()));
}

void UserManager::editUser_verify()
{
    User tempUser;
    User tempUser2;
    bool dup1 = false;
    bool dup2 = false;
    bool dup3 = false;
    tempUser.readUser(ui->editUser_LIDLine->text().toLong());
    for (int i = 0 ; i < getNumUser() ; ++i)
    {
        tempUser2.readUser(i+1);
        if (tempUser2.getUserID() != tempUser.getUserID())
        {
            if (tempUser2.getUserID() == ui->editUser_userIDLine->text().toLong())
                dup1 = true;
            if (tempUser2.getUserPID() == ui->editUser_userPIDLine->text().toLong())
                dup2 = true;
            if (tempUser2.getMailAddr() == ui->edituser_mailLine->text().toStdString())
                dup3 = true;
        }
        // No else
    }

    ui->editUser_confirmButton->setEnabled(!dup1 && !dup2 && !dup3);
    ui->editUser_dupEmail->setVisible(dup3);
    ui->editUser_dupPID->setVisible(dup2);
    ui->editUser_dupUID->setVisible(dup1);

}
void UserManager::editUser_verify_2()
{
    // Check account
    Account tempA;
    Account tempA2;
    bool dup2 = false;
    tempA.readData(ui->editUser_editAccount_aID->text().toLong());
    for (int i = 0 ; i < getFAccount() ; ++i)
    {
        tempA2.readData(i+1);
        if (tempA2.getUserName() != tempA.getUserName())
        {
            if (tempA2.getUserName() == ui->editUser_editAccount_USN->text().toStdString())
            {
                dup2 = true;
            }
        }
    }

    ui->editUser_editAccount_save->setEnabled(!dup2);
    ui->editUser_dupUSNLabel->setVisible(dup2);
}


void UserManager::searchUser_search()
{

    ui->findUserView->setRowCount(0);
    enum { F_LIBID = 0,F_PID =1 , F_UID =2, F_NAME = 3, F_MAIL =4, F_DOB =5, F_JOB = 6, F_NACC = 7, F_BUTTON = 8 };
    std::string findKey = ui->findUser_findLine->text().toStdString();
    User tempU;
    int counter = 0;
    for (int i = 0 ; i < getNumUser() ; ++i)
    {
        tempU.readUser(i+1);
        if (tempU.getLibID() != 0)
            if (tempU.getFullName().find(findKey) != std::string::npos
                    || tempU.getDOB().find(findKey) != std::string::npos
                    || tempU.getMailAddr().find(findKey) != std::string::npos
                    || tempU.getJob().find(findKey) != std::string::npos
                    || std::to_string(tempU.getLibID()).find(findKey) != std::string::npos
                    || std::to_string(tempU.getUserID()).find(findKey) != std::string::npos
                    || std::to_string(tempU.getUserPID()).find(findKey) != std::string::npos)
            {
                ui->findUserView->setRowCount(counter+1);
                ui->findUserView->setItem(counter,F_LIBID, new QTableWidgetItem(QString::number(tempU.getLibID())));
                ui->findUserView->setItem(counter,F_PID, new QTableWidgetItem(QString::number(tempU.getUserPID())));
                ui->findUserView->setItem(counter,F_UID,new QTableWidgetItem(QString::number(tempU.getUserID())));
                ui->findUserView->setItem(counter, F_NAME, new QTableWidgetItem(QString(tempU.getFullName().c_str())));
                ui->findUserView->setItem(counter, F_MAIL, new QTableWidgetItem(tempU.getMailAddr().c_str()));
                ui->findUserView->setItem(counter,F_DOB, new QTableWidgetItem(QString(tempU.getDOB().c_str())));
                ui->findUserView->setItem(counter,F_JOB, new QTableWidgetItem(tempU.getJob().c_str()));
                ui->findUserView->setItem(counter,F_NACC, new QTableWidgetItem(QString::number(tempU.getNumAccount())));
                QPushButton *listB = new QPushButton;
                QHBoxLayout *listLayout = new QHBoxLayout;
                QWidget* listWidget = new QWidget;
                listB->setText("Chi tiết");
                listLayout->addWidget(listB);
                listLayout->setAlignment(Qt::AlignCenter);
                listLayout->setContentsMargins(0, 0, 0, 0);
                listWidget->setLayout(listLayout);
                ui->findUserView->setCellWidget(counter,F_BUTTON,listWidget);
                connect(listB, &QPushButton::clicked, [=]{editUser_search(ui->findUserView->item(counter,F_LIBID)->text()
                                                                        .toLong());});
                ++counter;
            }

    }

    if (counter != 0 )
    {
        ui->findUserView->setVisible(true);
        ui->finduser_nFoundLabel->setVisible(false);
    }
    else
    {
        ui->findUserView->setVisible(false);
        ui->finduser_nFoundLabel->setVisible(true);
    }
    ui->implementField->setCurrentIndex(U_FIND);
}

void UserManager::addUser_clear()
{
    ui->usnErrLabel_adduser->setVisible(false);
    ui->mailErrLabel_addUser->setVisible(false);
    ui->userIDErrLabel_addUser->setVisible(false);
    ui->userPIDErrLabel_addUser->setVisible(false);
    ui->confirmButton_addUser->setEnabled(false);


    ui->nameLine_addUser->clear();
    ui->dobLine_addUser->clear();
    ui->jobLine_addUser->clear();
    ui->mailLine_addUser->clear();
    ui->usnLine_addUser->clear();
    ui->pwLine_addUser->clear();
    ui->userID_addUser->clear();
    ui->userPID_addUser->clear();
}


void UserManager::changePW_find()
{
    long accID = ui->changePW_findLine->text().toLong();
    Account tempA;
    tempA.readData(accID);
    if (tempA.getAccountID() == 0)  // If not found
    {
        ui->changePW_nFoundLabel->setVisible(true);
        ui->changePW_mainForm->setVisible(false);
    }
    else
    {
        ui->changePW_nFoundLabel->setVisible(false);
        ui->changePW_accID->setText(QString::number(tempA.getAccountID()));
        ui->changePW_USN->setText(QString(tempA.getUserName().c_str()));
        ui->changePW_mainForm->setVisible(true);
    }
}

void UserManager::changePW_save()
{
    long aid = ui->changePW_accID->text().toLong();
    std::string pwd = ui->changePW_PW->text().toStdString();
    Account tempA;
    tempA.readData(aid);
    tempA.setPassword(pwd);
    tempA.saveData();

    ui->changePW_PW->clear();
    ui->changePW_rePW->clear();
    ui->changePW_successLabel->setVisible(true);
    ui->changePW_confirmButton->setEnabled(false);
}
void UserManager::changePW_verify()
{
    if (ui->changePW_PW->text() != ui->changePW_rePW->text() || ui->changePW_PW->text().isEmpty() || ui->changePW_rePW->text().isEmpty())
        ui->changePW_confirmButton->setEnabled(false);
    else
        ui->changePW_confirmButton->setEnabled(true);

}

void UserManager::changePW_clear()
{
    ui->changePW_nFoundLabel->setVisible(false);
    ui->changePW_mainForm->setVisible(false);
    ui->changePW_accID->clear();
    ui->changePW_USN->clear();
    ui->changePW_PW->clear();
    ui->changePW_rePW->clear();
    ui->changePW_successLabel->setVisible(true);
    ui->changePW_confirmButton->setEnabled(false);
}
void UserManager::searchUser_connect()
{
    ui->findUserView->setVisible(false);
    ui->findUserView->setRowCount(0);
    ui->finduser_nFoundLabel->setVisible(false);

    ui->searchAccount_nFoundLabel->setVisible(false);
    ui->searchAccount_table->setVisible(false);
}
void UserManager::addAccount_beg()
{
    ui->implementField->setCurrentIndex(U_ADD_ACC);
    User tempU;
    tempU.readUser(ui->editUser_LIDLine->text().toLong());
    ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);
    ui->addAccount_ALine->setText(QString::number(User::getFAccount() + 1));
    ui->addAccount_libID->setText(QString::number(tempU.getLibID()));
    ui->addAccount_nameLine->setText(QString(tempU.getFullName().c_str()));


}
void UserManager::addAccount_clear()
{
    ui->addAccount_addLabel->setVisible(false);
    ui->addAccount_libID->clear();
    ui->addAccount_nameLine->clear();
    ui->addAccount_pwLine->clear();
    ui->addAccount_repwLine->clear();
    ui->addAccount_usnLine->clear();

    ui->addAccount_pwLabel->setVisible(false);
    ui->addAccount_usnLabel->setVisible(false);
    ui->addAccount_failLabel->setVisible(false);
    ui->addAccount_repwLabel_2->setVisible(false);
}

void UserManager::addAccount_verify()
{
    bool enable = true;
    bool dupUSN = false;
    User tempU;

    Account tempA;
    for (int i = 0 ; ((i < getFAccount()) && (!dupUSN)); ++i)
    {
        tempA.readData(i+1);
        qDebug() << "AAA" ;
        if (tempA.getUserName() == ui->addAccount_usnLine->text().toStdString())
            dupUSN = true;
    }
    qDebug() << dupUSN;
    ui->addAccount_usnLabel->setVisible(dupUSN);
    if (ui->addAccount_repwLine->text() != ui->addAccount_pwLine->text())
    {
        enable=false;
        ui->addAccount_repwLabel_2->setVisible(true);
    }
    else
        ui->addAccount_repwLabel_2->setVisible(false);


    if (ui->addAccount_pwLine->text().isEmpty())
    {
        enable = false;
        ui->addAccount_pwLabel->setVisible(true);
    }
    else
        ui->addAccount_pwLabel->setVisible(false);

    if (ui->addAccount_repwLine->text().isEmpty())
    {
        enable = false;
        ui->addAccount_repwLabel_2->setVisible(true);
    }
    else
        ui->addAccount_repwLabel_2->setVisible((ui->addAccount_repwLine->text() != ui->addAccount_pwLine->text()));

    if (ui->addAccount_usnLine->text().isEmpty())
    {
        enable = false;
        ui->addAccount_usnLabel->setVisible(true);
    }
    else
        ui->addAccount_usnLabel->setVisible(dupUSN);
    tempU.readUser(ui->addAccount_libID->text().toLong());
    ui->addAccount_addButton->setEnabled(enable && !dupUSN && tempU.getNumAccount() < 5);

}

void UserManager::verifySignup()
{
    ui->verifySignupView->setRowCount(0);
    enum {ID = 0, NAME = 1, DOB = 2, JOB = 3,EMAIL = 4, BUTTON};
    Account tempAcc;
    User tempUser;
    int counter = 0;
    for (int i = 0 ; i < getFAccount() ; ++i)
    {
        tempAcc.readData(i+1);
        if (tempAcc.getState() == A_U_WAIT_VERIFY)
        {
            tempUser.readUser(tempAcc.getLibID());
            ui->verifySignupView->setRowCount(counter + 1);
            ui->verifySignupView->setItem(counter,ID,new QTableWidgetItem(QString::number(tempUser.getLibID())));
            ui->verifySignupView->setItem(counter, NAME,new QTableWidgetItem(QString(tempUser.getFullName().c_str())));
            ui->verifySignupView->setItem(counter,DOB, new QTableWidgetItem(QString(tempUser.getDOB().c_str())));
            ui->verifySignupView->setItem(counter, JOB, new QTableWidgetItem(QString(tempUser.getJob().c_str())));
            ui->verifySignupView->setItem(EMAIL, EMAIL, new QTableWidgetItem(QString(tempUser.getMailAddr().c_str())));

            QPushButton *listB = new QPushButton;   // Xac thuc
            QPushButton *listB2 = new QPushButton;  // Tu choi
            QHBoxLayout *listLayout = new QHBoxLayout;
            QWidget* listWidget = new QWidget;
            listB->setText("Xác thực");
            listB2->setText("Từ chối");
            listLayout->addWidget(listB);
            listLayout->addWidget(listB2);
            listLayout->setAlignment(Qt::AlignCenter);
            listLayout->setContentsMargins(0, 0, 0, 0);
            listWidget->setLayout(listLayout);
            ui->verifySignupView->setCellWidget(counter,BUTTON,listWidget);
            connect(listB, &QPushButton::clicked, [=]{verifySignup_accept_i(ui->verifySignupView->item(counter,ID)->text().toLong());});
            connect(listB2, &QPushButton::clicked, [=]{verifySignup_cancel_i(ui->verifySignupView->item(counter,ID)->text().toLong());
                ui->verifySignupView->removeRow(counter);});
            ++counter;

        }
    }
    if (counter != 0)
    {
        ui->verifySignupView->setVisible(true);
        ui->verifySignup_nFoundLabel->setVisible(false);
    }
    else
    {
        ui->verifySignupView->setVisible(false);
        ui->verifySignup_nFoundLabel->setVisible(true);
    }
    qDebug() << counter ;
    ui->implementField->setCurrentIndex(U_VERIFY_SIGNUP);
}
void UserManager::verifySignup_accept_i(long uid)
{
    editUser_search(uid);
    ui->implementField->setCurrentIndex(U_EDIT_USER);
}

void UserManager::verifySignup_cancel_i(long uid)
{
    User tempUser;
    tempUser.readUser(uid);
    Account tempA;
    for (int i  = 0 ; i < tempUser.getNumAccount() ; ++i)
    {
        tempA.readData(tempUser.getAccountList()[i]);
        if (tempA.getState() == A_U_WAIT_VERIFY)
        {
            Account blankA;
            blankA.saveData(tempA.getAccountID());
        }
    }

    if (tempUser.getState() == A_U_WAIT_VERIFY)
    {
        User blankUser;
        blankUser.saveUser(tempUser.getLibID());
    }
}
void UserManager::addAccount_save()
{
    std::string role = "000";
    role[0] = (ui->addAccount_reader->isChecked() ? '1' : 0);
    role[1] = (ui->addAccount_librarian->isChecked() ? '1' : 0);
    role[2] = (ui->addAccount_usermanager->isChecked() ? '1' : 0);
    Account newA(ui->addAccount_libID->text().toLong(),ui->addAccount_ALine->text().toLong(),
                 ui->addAccount_usnLine->text().toStdString(), ui->addAccount_pwLine->text().toStdString(),
                 role, ui->addAccount_role->currentIndex());
    newA.saveData();
    long lid = ui->addAccount_libID->text().toLong();
    User tempUser;
    tempUser.readUser(lid);
    qDebug() << tempUser.getLibID();
    tempUser.addMoreAccount(newA.getAccountID());
    tempUser.saveUser();
    setFAccount(getFAccount() + 1);
    ui->addAccount_addLabel->setVisible(true);
    ui->addAccount_addButton->setEnabled(false);
    ui->addAccount_ALine->setText(QString::number(User::getFAccount() +1));
    ui->addAccount_addButton->setEnabled(false);

}

void UserManager::addAccount_connect()
{
    User tempU;
    tempU.readUser(ui->editUser_LIDLine->text().toLong());
    connect(ui->addAccount_ALine,&QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});
    connect(ui->addAccount_libID, &QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});
    connect(ui->addAccount_nameLine,&QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});
    connect(ui->addAccount_pwLine,&QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});
    connect(ui->addAccount_repwLine,&QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});
    connect(ui->addAccount_usnLine,&QLineEdit::textChanged, [=]{ui->addAccount_addLabel->setVisible(false);ui->addAccount_addButton->setEnabled(tempU.getNumAccount()<5);});

    connect(ui->addAccount_librarian, &QRadioButton::toggled, [=]{ui->addAccount_addLabel->setVisible(false);});
    connect(ui->addAccount_reader, &QRadioButton::toggled, [=]{ui->addAccount_addLabel->setVisible(false);});
    connect(ui->addAccount_usermanager, &QRadioButton::toggled, [=]{ui->addAccount_addLabel->setVisible(false);});
    connect(ui->addAccount_backButton, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(U_EDIT_USER);});

    connect(ui->addAccount_repwLine, &QLineEdit::textChanged, [=]{addAccount_verify();});
    connect(ui->addAccount_pwLine, &QLineEdit::textChanged, [=]{addAccount_verify();});
    connect(ui->addAccount_usnLine, &QLineEdit::textChanged, [=]{addAccount_verify();});

    connect(ui->addAccount_addButton, &QPushButton::clicked, [=]{addAccount_save();ui->addAccount_addLabel->setVisible(true);});
}


void UserManager::changePW_connect()
{
    connect(ui->changePW_findButton, SIGNAL(clicked(bool)), this, SLOT(changePW_find()));
    connect(ui->changePW_confirmButton,&QPushButton::clicked, [=]{changePW_save();});

    connect(ui->changePW_accID,&QLineEdit::textChanged, [=]{ui->changePW_successLabel->setVisible(false);});
    connect(ui->changePW_findLine,&QLineEdit::textChanged, [=]{ui->changePW_successLabel->setVisible(false);});
    connect(ui->changePW_PW,&QLineEdit::textChanged, [=]{ui->changePW_successLabel->setVisible(false);changePW_verify();});
    connect(ui->changePW_rePW,&QLineEdit::textChanged, [=]{ui->changePW_successLabel->setVisible(false);changePW_verify();});
    connect(ui->changePW_USN,&QLineEdit::textChanged, [=]{ui->changePW_successLabel->setVisible(false);});
}

void UserManager::UserManager::logout()
{
    close();
    StartProgram *c = new StartProgram();
    c->show();
}
void UserManager::editUser_connect()
{
    connect(ui->editUser_backButton_2, &QPushButton::clicked, [=]{editUser_clear();ui->implementField->setCurrentIndex(U_EDIT_USER);});

    connect(ui->editUser_addAButton, &QPushButton::clicked, [=]{addAccount_beg();});

    connect(ui->editUser_editAccount_LIBID, &QLineEdit::textChanged, [=]{ui->editUser_aSuccLabel->setVisible(false);});
    connect(ui->editUser_editAccount_USN, &QLineEdit::textChanged, [=]{ui->editUser_aSuccLabel->setVisible(false);});
    connect(ui->editUser_editAccount_PW, &QLineEdit::textChanged, [=]{ui->editUser_aSuccLabel->setVisible(false);});
    connect(ui->editUser_editAccount_usermanager, &QRadioButton::toggled, [=]{ui->editUser_aSuccLabel->setVisible(false);});
    connect(ui->editUser_editAccount_reader, &QRadioButton::toggled, [=]{ui->editUser_aSuccLabel->setVisible(false);});
    connect(ui->editUser_editAccount_librarian, &QRadioButton::toggled, [=]{ui->editUser_aSuccLabel->setVisible(false);});

    connect(ui->editUser_editAccount_backButton, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(U_EDIT_USER);});

    connect(ui->editUser_nameLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->editUser_userIDLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->editUser_userPIDLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->editUser_DOBLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->editUser_JOBLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->edituser_mailLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});
    connect(ui->editUser_LIDLine, &QLineEdit::textChanged, [=]{ui->editUser_uSeccLabel->setVisible(false);});

    connect(ui->editUser_findButton, &QPushButton::clicked ,[=]{editUser_search(ui->editUser_libFinndLine->text().toLong());});
    connect(ui->editUser_confirmButton, SIGNAL(clicked(bool)), this, SLOT(editUser_save()));

    connect(ui->editUser_acc1Button, &QPushButton::clicked, [=]{editUser_editAccount(ui->editUser_acc1Label->text());});
    connect(ui->editUser_acc2Button, &QPushButton::clicked, [=]{editUser_editAccount(ui->editUser_acc2Label->text());});
    connect(ui->editUser_acc3Button, &QPushButton::clicked, [=]{editUser_editAccount(ui->editUser_acc3Label->text());});
    connect(ui->editUser_acc4Button, &QPushButton::clicked, [=]{editUser_editAccount(ui->editUser_acc4Label->text());});
    connect(ui->editUser_acc5Button, &QPushButton::clicked, [=]{editUser_editAccount(ui->editUser_acc5Label->text());});

    connect(ui->editUser_editAccount_save, SIGNAL(clicked(bool)), this, SLOT(editUser_saveAccount()));

    connect(ui->editUser_editAccount_USN, &QLineEdit::textChanged, [=]{editUser_verify_2();});
    connect(ui->editUser_userIDLine, &QLineEdit::textChanged, [=]{editUser_verify();});
    connect(ui->editUser_userPIDLine, &QLineEdit::textChanged, [=]{editUser_verify();});
    connect(ui->edituser_mailLine, &QLineEdit::textChanged, [=]{editUser_verify();});

    connect(ui->editUser_delButton, &QPushButton::clicked, [=]{editUser_deleteU();});

    connect(ui->editUser_acc1delButton, &QPushButton::clicked, [=]{editUser_deleteA(1);ui->editUser_acc1Group_2->setVisible(false);});
    connect(ui->editUser_acc2delButton, &QPushButton::clicked, [=]{editUser_deleteA(2);ui->editUser_acc2Group_2->setVisible(false);});
    connect(ui->editUser_acc3delButton, &QPushButton::clicked, [=]{editUser_deleteA(3);ui->editUser_acc3Group_2->setVisible(false);});
    connect(ui->editUser_acc4delButton, &QPushButton::clicked, [=]{editUser_deleteA(4);ui->editUser_acc4Group_2->setVisible(false);});
    connect(ui->editUser_acc5delButton, &QPushButton::clicked, [=]{editUser_deleteA(5);ui->editUser_acc5Group_2->setVisible(false);});

    connect(ui->addAccount_backButton, &QPushButton::clicked,[=]{editUser_search(ui->editUser_LIDLine->text().toLong());});
}

void UserManager::setInfo(long aid)
{
    Account account;
    User user;
    account.readData(aid);
    user.readUser(account.getLibID());
    ui->info_label->setVisible(false);
    ui->info_accIDLine->setText(QString::number(aid));
    ui->info_dobLine->setText(QString::fromStdString(user.getDOB()));
    ui->info_emailLine->setText(QString::fromStdString(user.getMailAddr()));
    ui->info_jobLine->setText(QString::fromStdString(user.getJob()));
    ui->info_libLine->setText(QString::number(user.getLibID()));
    ui->info_nameLine->setText(QString::fromStdString(user.getFullName()));
    ui->info_pwLine->setText(QString::fromStdString(account.getPassword()));
    ui->info_usnLine->setText(QString::fromStdString(account.getUserName()));
    connect(ui->info_saveButton, &QPushButton::clicked, [=]{info_save();});
}
void UserManager::searchAccount_search()
{
    enum {LIBID = 0, ACCID = 1, USN = 2, PW = 3, READER = 4, LIBRARIAN = 5, USM = 6};
    std::string sKey = ui->searchAccount_searchLine->text().toStdString();
    Account account;
    int counter = 0;
    for (int i = 0 ; i < getFAccount() ; ++i)
    {
        account.readData(i+1);
        if (account.getUserName().find(sKey) != std::string::npos)
        {
            ++counter;
            ui->searchAccount_table->setRowCount(counter);
            ui->searchAccount_table->setItem(counter-1,LIBID, new QTableWidgetItem(QString::number(account.getLibID())));
            ui->searchAccount_table->setItem(counter-1,ACCID, new QTableWidgetItem(QString::number(account.getAccountID())));
            ui->searchAccount_table->setItem(counter-1,USN, new QTableWidgetItem(QString::fromStdString(account.getUserName())));
            ui->searchAccount_table->setItem(counter-1,PW, new QTableWidgetItem(QString::fromStdString(account.getPassword())));
            ui->searchAccount_table->setItem(counter-1,READER, new QTableWidgetItem((account.getRole()[0] == '1' ? "X" : "")));
            ui->searchAccount_table->setItem(counter-1,LIBRARIAN, new QTableWidgetItem((account.getRole()[1] == '1' ? "X" : "")));
            ui->searchAccount_table->setItem(counter-1,USM, new QTableWidgetItem((account.getRole()[2] == '1' ? "X" : "")));

        }
    }
    if (counter == 0)
    {
        ui->searchAccount_nFoundLabel->setVisible(true);
        ui->searchAccount_table->setVisible(false);
    }
    else
    {
        ui->searchAccount_nFoundLabel->setVisible(false);
        ui->searchAccount_table->setVisible(true);
    }
}

void UserManager::info_save()
{
    Account account;
    account.readData(ui->info_accIDLine->text().toLong());
    account.setPassword(ui->info_pwLine->text().toStdString());
    account.saveData();
    ui->info_label->setVisible(true);
    connect(ui->info_pwLine, &QLineEdit::textChanged, [=]{ui->info_label->setVisible(false);});
}
