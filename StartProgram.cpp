#include "StartProgram.h"
#include <QTime>
#include <QTimer>
#include "ui_StartProgram.h"

enum {S_LOGIN = 0, S_ROLE = 1, S_REGU = 2, S_REGU_REGA = 3, S_REGSUCCESS = 4, S_SIGNUP_OPT = 5, S_REGA =6, S_REGA_2 = 7};

StartProgram::StartProgram(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StartProgram)
{
    ui->setupUi(this);
    setCurrentIndex(0);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->loginNotif->setVisible(false);
    connect(ui->loginButton,SIGNAL(clicked(bool)), this, SLOT(userLogin()));
    ui->loginButton->setEnabled(false);
    ui->login_readerButton->setVisible(false);
    ui->login_librarianButton->setVisible(false);
    ui->login_usermanagerButton->setVisible(false);


    connect(ui->login_pwLine, SIGNAL(textChanged(const QString &)), this, SLOT(enableLoginButton()));
    connect(ui->login_usnLine, SIGNAL(textChanged(const QString &)), this, SLOT(enableLoginButton()));
    connect(ui->signupButton, &QPushButton::clicked , [=]{setCurrentIndex(S_SIGNUP_OPT);});
    connect(ui->login_confirmButton, SIGNAL(clicked(bool)), this, SLOT(loginRole()));
    connect(ui->regUser_confirmButton_1, &QPushButton::clicked , [=]{setCurrentIndex(3);});
    connect(ui->regUser_UIDLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_usnLine,SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect    (ui->regUser_repwLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_pwLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_PIDLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_mailLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_nameLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_jobLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_dobLine, SIGNAL(textChanged(QString)), this, SLOT(enableSignUp()));
    connect(ui->regUser_regButton, SIGNAL(clicked(bool)), this, SLOT(saveData()));

    ui->regUser_UIDdupLabel->setVisible(false);
    ui->regUser_PIDdupLabel->setVisible(false);
    ui->regUser_maildupLabel->setVisible(false);
    ui->dupUSNLabel->setVisible(false);
    ui->dupPWLabel->setVisible(false);

    ui->regUser_regButton->setEnabled(false);
    ui->regUser_confirmButton_1->setEnabled(false);

    connect(ui->regUser_backButton, &QPushButton::clicked,[=]{setCurrentIndex(0);});
    connect(ui->regUser_backButton_2, &QPushButton::clicked,[=]{setCurrentIndex(2);});

    connect(ui->newUserButton, &QPushButton::clicked, [=]{setCurrentIndex(2);});


    connect(ui->login_backButton, &QPushButton::clicked, [=]{setCurrentIndex(0);});
    connect(ui->regUser_backButton_3, &QPushButton::clicked, [=]{setCurrentIndex(0);});
    connect(ui->regUser_exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(ui->oldUserButton, &QPushButton::clicked, [=]{setCurrentIndex(S_REGA);});

    ui->regA_erLabel->setVisible(false);
    connect(ui->regA_confirmButton, SIGNAL(clicked(bool)), this, SLOT(signup_verify()));
    connect(ui->regA_regButton, SIGNAL(clicked(bool)), this, SLOT(signup_verify_2()));
    connect(ui->regA_backButton,&QPushButton::clicked, [=]{setCurrentIndex(0);});
    connect(ui->regA_backButton_2,&QPushButton::clicked, [=]{setCurrentIndex(S_REGA);});
    ui->regA_errLabel->setVisible(false);
    ui->regA_erLabel2->setVisible(false);

    connect(ui->resetProg, &QPushButton::clicked, [=]{reset();});

}
void StartProgram::userLogin()
{
    std::string userName = ui->login_usnLine->text().toStdString();
    std::string password = ui->login_pwLine->text().toStdString();
    bool isLogin = false;
    for (int i = 1 ; i <= User::getFAccount() && !isLogin; ++i)
    {
        tempAccount.readData(i);
        if (tempAccount.getPassword() == password && tempAccount.getUserName() == userName)
            isLogin=true;
    }
    User user;
    user.readUser(tempAccount.getLibID());
    if (isLogin && tempAccount.getState() == A_U_NORMAL && user.getState() == A_U_NORMAL)
    {
        tempUser.readUser(tempAccount.getLibID());
        if (tempAccount.getRole()[0] == '1')
            ui->login_readerButton->setVisible(true);
        if (tempAccount.getRole()[1] == '1')
            ui->login_librarianButton->setVisible(true);
        if (tempAccount.getRole()[2] == '1')
            ui->login_usermanagerButton->setVisible(true);
        ui->xLabel->setVisible(false);
        ui->xLabel->setText(QString::number(tempAccount.getAccountID()));
        setCurrentIndex(1);
    }
    else
    {
        ui->loginNotif->setText("Đăng nhập thất bại");
        ui->loginNotif->setVisible(true);
    }
}
void StartProgram::enableLoginButton()
{
    if (ui->login_usnLine->text().isEmpty() || ui->login_pwLine->text().isEmpty())
        ui->loginButton->setEnabled(false);
    else ui->loginButton->setEnabled(true);
}
void StartProgram::loginRole()
{
    this->close();
    long aid = ui->xLabel->text().toLong();
    if (ui->login_readerButton->isChecked())
    {
        Reader* tempReader = new Reader(tempUser);
        tempReader->showMaximized();
        tempReader->setInfo(aid);
    }
    else if (ui->login_librarianButton->isChecked())
    {
        Librarian* tempLibrarian = new Librarian(tempUser);
        tempLibrarian->showMaximized();
        tempLibrarian->setInfo(aid);
    }
    else if (ui->login_usermanagerButton->isChecked())
    {
        UserManager* tempUSM = new UserManager(tempUser);
        tempUSM->showMaximized();
        tempUSM->setInfo(aid);
    }
}
void StartProgram::saveData()
{
     User newUser(User::getNumUser() + 1,ui->regUser_UIDLine->text().toLong(), ui->regUser_PIDLine->text().toLong(),
                  ui->regUser_nameLine->text().toStdString(), ui->regUser_dobLine->text().toStdString(), ui->regUser_jobLine->text().toStdString(),
                  ui->regUser_mailLine->text().toStdString(),A_U_WAIT_VERIFY);

     Account newAccount(User::getNumUser() + 1,User::getFAccount() +1,ui->regUser_usnLine->text().toStdString(),ui->regUser_pwLine->text().toStdString(),"100", A_U_WAIT_VERIFY);
     User::setFAccount(User::getFAccount() + 1);
     User::setNumUser(User::getNumUser() + 1);
     newUser.addMoreAccount(newAccount.getAccountID());
     newUser.saveUser();
     newAccount.saveData();

     this->setCurrentIndex(4);
}
void StartProgram::enableSignUp()
{
    bool enable1 = true;
    bool enable2 = true;

    // Password check

    if (ui->regUser_pwLine->text().toStdString() == ui->regUser_repwLine->text().toStdString())
        ui->dupPWLabel->setVisible(false);
    else
    {
        enable2=false;
        ui->dupPWLabel->setVisible(true);
    }

    // Account check

    Account tempA;
    bool dup =false;
    for (int i = 0 ; i < User::getFAccount() && !dup ; ++i)
    {
        tempA.readData(i+1);
        if (tempA.getUserName() == ui->regUser_usnLine->text().toStdString())
            dup = true;
    }
    if (dup)
    {
        enable2 = false;
        ui->dupUSNLabel->setVisible(true);
    }
    else
         ui->dupUSNLabel->setVisible(false);

    // Email check

    User temp;
    bool dup2 = false;
    for (int i = 0 ; i < User::getNumUser() && !dup ; ++i)
    {
        temp.readUser(i+1);
        if (temp.getMailAddr() == ui->regUser_mailLine->text().toStdString())
            dup2 = true;
    }
    if (dup2)
    {
        ui->regUser_maildupLabel->setVisible(true);
        enable1 = false;
    }
    else
        ui->regUser_maildupLabel->setVisible(false);

    // PID check

    bool dup3 = false;
    for (int i = 0 ; i < User::getNumUser() && !dup ; ++i)
    {
        temp.readUser(i+1);
        if (temp.getUserPID() == ui->regUser_PIDLine->text().toLong())
            dup3 = true;
    }
    if (dup3)
    {
        enable1 = false;
        ui->regUser_PIDdupLabel->setVisible(true);
    }
    else
        ui->regUser_PIDdupLabel->setVisible(false);

    // User ID check

    bool dup4 = false;
    for (int i = 0 ; i < User::getNumUser() && !dup ; ++i)
    {
        temp.readUser(i+1);
        if (temp.getUserID() == ui->regUser_UIDLine->text().toLong())
            dup4 = true;
    }
    if (dup4)
    {
        ui->regUser_UIDdupLabel->setVisible(true);
        enable1 = false;

    }
    else
        ui->regUser_UIDdupLabel->setVisible(false);

    if (ui->regUser_dobLine->text().isEmpty())
        enable1 = false;
    if (ui->regUser_mailLine->text().isEmpty())
        enable1 = false;
    if (ui->regUser_jobLine->text().isEmpty())
        enable1 = false;
    if (ui->regUser_PIDLine->text().isEmpty())
        enable1 = false;
    if (ui->regUser_UIDLine->text().isEmpty())
        enable1 = false;
    if (ui->regUser_nameLine->text().isEmpty())
        enable1 = false;

    if (ui->regUser_usnLine->text().isEmpty())
        enable2 = false;
    if (ui->regUser_pwLine->text().isEmpty())
        enable2 = false;
    if (ui->regUser_repwLine->text().isEmpty())
        enable2 = false;

    ui->regUser_regButton->setEnabled(enable2);
    ui->regUser_confirmButton_1->setEnabled(enable1);

}
void StartProgram::resetProg()
{
    BookType blankBook;
    Book blankB;
    User blankUser;
    Account blankAccount;
    RentBook blankRent;
    Notification blankNotif;
    std::ofstream bookFout("book_data.txt");
    bookFout.seekp(0);
    std::ofstream accFout("account_data.txt");
    accFout.seekp(0);
    std::ofstream userFout("user_data.txt");
    userFout.seekp(0);
    std::ofstream rentFout("rent_data.txt");
    rentFout.seekp(0);
    std::ofstream notifFout("notif_data.txt");
    notifFout.seekp(0);
    std::ofstream book2Fout("book_data_list.txt");
    book2Fout.seekp(0);
    for (int i = 0; i < 10000; ++i)
    {
        bookFout.write(reinterpret_cast<char*>(&blankBook), sizeof(BookType));
        accFout.write(reinterpret_cast<char*>(&blankAccount), sizeof(Account));
        userFout.write(reinterpret_cast<char*>(&blankUser), sizeof(User));
        rentFout.write(reinterpret_cast<char*>(&blankRent), sizeof(RentBook));
        notifFout.write(reinterpret_cast<char*>(&blankNotif), sizeof(Notification));
        book2Fout.write(reinterpret_cast<char*>(&blankB), sizeof(Book));
    }
    std::ofstream resParam("foo.txt");

    resParam << "NumBookType:" << "\t\t" << 0 << std::endl;
    resParam << "NumUser: " << "\t\t"  << 1 << std::endl;
    resParam << "NumAccount: " << "\t\t"  << 2 << std::endl;
    resParam << "NumRent: " << "\t\t"  << 0 << std::endl;
    resParam << "NumNotif: " << "\t\t"  << 0 << std::endl;
    resParam << "NumBookType: " << "\t\t" << 0 << std::endl;
    resParam << "NumBook: " << "\t\t" << 0 << std::endl;
    User adminUser(1,1,1,"LIBPRO","20/04/1998","XXX","XXX",A_U_NORMAL);
    Account adminAcc(1,1,"admin","admin","111",A_U_NORMAL);
    Account admin2(1,2,"123","123","111",A_U_NORMAL);
    admin2.saveData();
    adminUser.addMoreAccount(1);
    adminUser.addMoreAccount(2);
    adminUser.saveUser();
    adminAcc.saveData();

    remove("param_data.txt");
    resParam.close();
    rename("foo.txt", "param_data.txt");
}
void StartProgram::signup_verify()
{
    User tempU;
    if (ui->regA_libLine->text().toLong() <= 0 || ui->regA_libLine->text().toLong()>= 10000)
    {
        ui->regA_erLabel->setVisible(true);
    }
    else
    {
        ui->regA_erLabel->setVisible(true);
        tempU.readUser(ui->regA_libLine->text().toLong());
        if (tempU.getUserID() == ui->regA_uidLine->text().toLong())
        {
                ui->regA_erLabel->setVisible(false);
                if (tempU.getNumAccount()<5)
                {
                    setCurrentIndex(S_REGA_2);
                    ui->regA_erLabel2->setVisible(false);
                }
                else
                    ui->regA_erLabel2->setVisible(true);
        }
        else
                ui->regA_erLabel->setVisible(true);
    }

    // Xác thực số lượng tài khoản


    connect(ui->regA_libLine, &QLineEdit::textChanged, [=]{ui->regA_erLabel->setVisible(false);});
    connect(ui->regA_uidLine, &QLineEdit::textChanged, [=]{ui->regA_erLabel->setVisible(false);});
}
void StartProgram::signup_verify_2()
{


    Account tempA;
    bool dup = false;
    for (int i = 0; i < User::getFAccount() && !dup ; ++i)
    {
        tempA.readData(i +1);
        if ( tempA.getUserName() == ui->regA_usnLine->text().toStdString())
            dup = true;
    }

    if (dup)
    {
        ui->regA_errLabel->setVisible(true);
        connect(ui->regA_usnLine, &QLineEdit::textChanged, [=]{ui->regA_errLabel->setVisible(false);});
        connect(ui->regA_pwLine, &QLineEdit::textChanged, [=]{ui->regA_errLabel->setVisible(false);});
        connect(ui->regA_repwLine, &QLineEdit::textChanged, [=]{ui->regA_errLabel->setVisible(false);});
    }
    else
    {
        ui->regA_errLabel->setVisible(false);
        User tempU;
        Account newA(ui->regA_libLine->text().toLong(),User::getFAccount() + 1,
                     ui->regA_usnLine->text().toStdString(), ui->regA_pwLine->text().toStdString(),
                     "100",A_U_WAIT_VERIFY);
        tempU.readUser(newA.getLibID());
        qDebug() << User::getFAccount() + 1;
        qDebug() << newA.getAccountID();
        tempU.addMoreAccount(newA.getAccountID());
        newA.saveData();
        tempU.saveUser();
        User::setFAccount(User::getFAccount() + 1);
        qDebug() << User::getFAccount();
        setCurrentIndex(S_REGSUCCESS);
    }
}
void StartProgram::reset()
{
    QString pw = QInputDialog::getText(this,"Thiết lập lại chương trình","Mật khẩu");
    if (pw == "123")
        resetProg();
    else
    {
        QMessageBox message;
        message.setWindowTitle("Thiết lập lại");
        message.setText("Sai mật khẩu");
        message.exec();
    }
}

StartProgram::~StartProgram()
{
    delete ui;
}
