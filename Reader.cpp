#include "Reader.h"
#include "ui_Reader.h"


enum {R_WELCOME = 0, R_FIND = 1, R_FIND_OPT = 2, R_RENT_HIS = 3, R_INFO = 4, R_FIND_CART = 5, R_FIND_DONE = 6, R_ABOUT = 7, R_NOTIF = 8, R_NOTIF_OPT = 9};

Reader::Reader(const User& x, QWidget *parent) :
    QMainWindow(parent), User(x),
    ui(new Ui::Reader)
{
    ui->setupUi(this);
    connect(ui->logOut_Button,&QPushButton::clicked, [=]{logout();} );

    findBook_clear();

    connect(ui->findBook_Button, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(R_FIND);});
    connect(ui->findBook_findButton, SIGNAL(clicked(bool)), SLOT(findBook_find()));
    ui->bookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cartView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->bookView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->cartView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rentHistoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rentHistoryView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->readNotifView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(ui->findBook_rentButton, SIGNAL(clicked(bool)), this, SLOT(findBook_addCart()));
    connect(ui->findBook_backButton_1,&QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(R_FIND);});
    connect(ui->findBook_cartButton, &QPushButton::clicked, [=]{findBook_cart();});
    connect(ui->findBook_confirmButton, SIGNAL(clicked(bool)), this, SLOT(findBook_rent()));
    connect(ui->findBook_backButton_3, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(0);});
    connect(ui->findBook_filtBox, SIGNAL(currentIndexChanged(int)), this, SLOT(findBook_find()));

    connect(ui->about_Button,&QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(R_ABOUT);});

    // Change passw
    // Rent history

    connect(ui->rentHistory_Button, SIGNAL(clicked(bool)), this, SLOT(rentHistory()));

    connect(ui->readNotif_Button, &QPushButton::clicked, [=]{readNotif_beg();});
    ui->findBook_confirmButton->setEnabled(true);

    connect(ui->info, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(R_INFO);});
    connect(ui->findBook_backButton2, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(R_FIND);});
}

Reader::~Reader()
{
    delete ui;
}
void Reader::findBook_find()
{
    enum {B_ID = 0, TITLE =1 , AUTHOR =2 , TYPE =3 , YEAR = 4, AMOUNT  = 5, TIMES_ACCESS = 6};
    std::string fString = ui->findBook_findLine->text().toStdString();
    ui->bookView->setRowCount(0);
    ui->bookView->setColumnCount(8);
    BookType tempB;
    std::vector<long> fBookID;
    auto allBook = [](BookType){return true;};
    auto availbook = [](BookType i){return (i.getNFree() != 0);};

    std::function<bool(BookType)> cond = allBook;
    switch (ui->findBook_filtBox->currentIndex())
    {
    case 0:
        cond = allBook;
        break;
    case 1:
        cond = availbook;
        break;
    default:
        break;
    }
    for (int i = 0 ; i < User::getNBookType() ; ++i)
    {
        tempB.readData(i+1);
        if (tempB.getBookID() != 0)
        if ((Search(tempB.getName(), fString)
                || Search(tempB.getAuthor(),fString)
                || Search(tempB.getType(),fString)
                || Search(tempB.getSummary(),fString)
                || Search(std::to_string(tempB.getYear()),fString))
                && cond(tempB))
            fBookID.push_back(tempB.getBookID());
    }
    if (fBookID.empty())            // If not found
    {
        ui->bookView->setVisible(false);
        ui->findBook_nFoundLabel->setVisible(true);

    }
    else            // If found
    {
        int row = fBookID.size();
        ui->findBook_nFoundLabel->setVisible(false);
        ui->bookView->setRowCount(row);

        for (int i = 0 ; i < row ; ++i)
        {
            tempB.readData(fBookID[i]);
            ui->bookView->setItem(i, B_ID, new QTableWidgetItem(QString::number(tempB.getBookID())));
            ui->bookView->setItem(i, TITLE, new QTableWidgetItem(QString(tempB.getName().c_str())));
            ui->bookView->setItem(i, AUTHOR, new QTableWidgetItem(QString(tempB.getAuthor().c_str())));
            ui->bookView->setItem(i, YEAR , new QTableWidgetItem(QString::number(tempB.getYear())));
            ui->bookView->setItem(i, TIMES_ACCESS, new QTableWidgetItem(QString::number(tempB.getTimeAccess())));
            ui->bookView->setItem(i, TYPE, new QTableWidgetItem(QString(tempB.getType().c_str())));
            ui->bookView->setItem(i, AMOUNT, new QTableWidgetItem(QString::number(tempB.getNFree())));

            QPushButton *listB = new QPushButton;
            QHBoxLayout *listLayout = new QHBoxLayout;
            QWidget* listWidget = new QWidget;
            listB->setText("Chi tiết");
            listLayout->addWidget(listB);
            listLayout->setAlignment(Qt::AlignCenter);
            listLayout->setContentsMargins(0, 0, 0, 0);
            listWidget->setLayout(listLayout);
            ui->bookView->setCellWidget(i,7,listWidget);
            connect(listB, &QPushButton::clicked, [=]{findBook_opt(i);});
        }



        ui->bookView->setMinimumHeight(ui->bookView->sizeHint().height());
        ui->bookView->setVisible(true);

    }
}
void Reader::findBook_opt(long i)
{
    long bookID = ui->bookView->item(i,0)->text().toLong();
    BookType tempB;
    tempB.readData(bookID);


        tempB.setTimesAcess(tempB.getTimeAccess()+1);
        tempB.saveData();
        ui->findBook_authorLine->setText(QString(tempB.getAuthor().c_str()));
        ui->findBook_authorLine->setReadOnly(true);
        ui->findBook_bookIDLine->setText(QString::number(tempB.getBookID()));
        ui->findBook_bookIDLine->setReadOnly(true);
        ui->findBook_bookTitleLine->setText(QString(tempB.getName().c_str()));
        ui->findBook_bookTitleLine->setReadOnly(true);
        ui->findBook_timesALine->setText(QString::number(tempB.getTimeAccess()));
        ui->findBook_timesALine->setReadOnly(true);
        ui->findBook_typeLine->setText(QString(tempB.getType().c_str()));
        ui->findBook_typeLine->setReadOnly(true);
        ui->findBook_yearLine->setText(QString::number(tempB.getYear()));
        ui->findBook_yearLine->setReadOnly(true);
        ui->findBook_summary->document()->setPlainText(QString(tempB.getSummary().c_str()));
        ui->findBook_summary->setReadOnly(true);
        ui->findBook_dateLine->setMinimumDate(QDate::currentDate());
        ui->findBook_rentButton->setEnabled(tempB.getNFree()> 0);
        ui->implementField->setCurrentIndex(R_FIND_OPT);
}
void Reader::findBook_addCart()
{
    // Thêm vào giỏ
    ui->findBook_rentLabel->setVisible(false);
    long bookID = ui->findBook_bookIDLine->text().toLong();
    int day = 30;
    QDate rentD = ui->findBook_dateLine->date();
    QDate returnD = rentD.addDays(day);
    BookType tempB;
    ui->cartView->setRowCount(ui->cartView->rowCount()+1);
    enum { BTID = 0  , NAME = 1 ,  AUTHOR = 2, YEAR = 3,  RENTD = 4, EXPD = 5, OPT = 6};
    tempB.readData(bookID);
    int row = ui->cartView->rowCount()-1;
    ui->cartView->setItem(row,BTID, new QTableWidgetItem(QString::number(tempB.getBookID())));
    ui->cartView->setItem(row,NAME, new QTableWidgetItem(QString(tempB.getName().c_str())));
    ui->cartView->setItem(row,AUTHOR, new QTableWidgetItem(QString(tempB.getAuthor().c_str())));
    ui->cartView->setItem(row,YEAR, new QTableWidgetItem(QString::number(tempB.getYear())));
    ui->cartView->setItem(row,RENTD, new QTableWidgetItem(QDateToString(rentD)));
    ui->cartView->setItem(row,EXPD, new QTableWidgetItem(QDateToString(returnD)));

    QPushButton *listB = new QPushButton;
    QHBoxLayout *listLayout = new QHBoxLayout;
    QWidget* listWidget = new QWidget;
    listB->setText("Xóa");
    listLayout->addWidget(listB);
    listLayout->setAlignment(Qt::AlignCenter);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listWidget->setLayout(listLayout);
    ui->cartView->setCellWidget(row,OPT,listWidget);
    connect(listB, &QPushButton::clicked, [=]{ui->cartView->removeRow(row);});

    ui->findBook_rentLabel->setVisible(true);
}
void Reader::findBook_rent()
{

    enum { BTID = 0  , NAME = 1 ,  AUTHOR = 2, YEAR = 3, AMOUNT = 4, RENTD = 5, EXPD = 6, OPT = 7};
    Account tempA;
    QDate rentD;
    BookType bookType;
    tempA.readData(ui->info_accIDLine->text().toLong());
    for (int i = 0 ; i < ui->cartView->rowCount() ; ++i)
    {
        // long rid = 0, long aid = 0, QDate = {}, QDate = {}, QDate = {}, long bid = 0, long btid = 0, int st = RENT_NORMAL, long = 0);
        rentD = stringToQDate(ui->cartView->item(i,RENTD)->text());
        RentBook newRent(User::getFNumRent() +1, ui->info_accIDLine->text().toLong(),
                         QDate::currentDate(), rentD, rentD.addDays(30),
                         0,ui->cartView->item(i,BTID)->text().toLong(),WAIT_RENT);
        bookType.readData(ui->cartView->item(i,BTID)->text().toLong());
        bookType.setNFree(bookType.getNFree() - 1);
        bookType.saveData();
        newRent.saveData();
        tempA.addRentRecord(newRent.getRentID());
        setFNumRent(getFNumRent() +1);
    }
    findBook_clear();
    ui->implementField->setCurrentIndex(R_FIND_DONE);
    tempA.saveData();

}
void Reader::findBook_cart()
{
    Account tempA;
    RentBook tempR;
    tempA.readData(ui->info_accIDLine->text().toLong());
    int num2 = 0;

    for (int i = 0 ; i < tempA.getNumRent() ; ++i)
    {
        tempR.readData(tempA.getRentList()[i]);
        if (tempR.getState() == RENT_NORMAL)
            ++num2;
    }
    ui->findBook_countLabel->setText("Hiện đang mượn " + QString::number(num2)
                                     + " cuốn sách\n Đã từng mượn " + QString::number(tempA.getNumRent()) + "/" + QString::number(MAX_RENT2) + " lần" );
    if (tempA.getNumRent() + ui->cartView->rowCount() > MAX_RENT2)
    {

        ui->findBook_confirmRentLabel->setText("Số lượng sách vượt giá định mức đôi với bạn");
        ui->findBook_confirmRentLabel->setVisible(true);
    }
    else
    {
        ui->findBook_confirmButton->setDisabled(false);
        ui->findBook_confirmRentLabel->setVisible(false);
    }
    if (ui->cartView->rowCount() == 0)
        ui->findBook_confirmButton->setDisabled(true);
    ui->implementField->setCurrentIndex(R_FIND_CART);
}
void Reader::findBook_clear()
{
    ui->bookView->setVisible(false);
    ui->implementField->setCurrentIndex(0);
    ui->findBook_nFoundLabel->setVisible(false);
    ui->bookView->setRowCount(0);
    ui->cartView->setRowCount(0);
    ui->implementField->setCurrentIndex(0);
    ui->findBook_confirmRentLabel->setVisible(false);
    ui->findBook_rentLabel->setVisible(false);
}

QString Reader::QDateToString(const QDate& date)
{
    QString ans;
    ans = (QString::number(date.day()).size() == 1 ? "0" + QString::number(date.day()) : QString::number(date.day())) + "/"
            + (QString::number(date.month()).size() == 1 ? "0" + QString::number(date.month()) : QString::number(date.month())) + "/"
            + QString::number(date.year());
    return ans;
}
QDate Reader::stringToQDate(QString date)
{
    QDate ans = QDate::fromString(date,"dd/MM/yyyy");

    return ans;
}



void Reader::rentHistory()
{
    Account tempA;
    ui->rentHistoryView->setRowCount(0);
    tempA.readData(ui->info_accIDLine->text().toLong());

    auto allResult = [](RentBook){return true;};
    auto waitRent = [](RentBook i){return (i.getState() == WAIT_RENT);};
    auto lost = [](RentBook i){return (i.getState() == RENT_LOST);};
    auto renting = [](RentBook i){return (i.getState() == RENT_NORMAL);};
    auto rentFail = [](RentBook i){return (i.getState() == RENT_FAIL);};
    auto rented = [](RentBook i){return (i.getState() == RENT_BACKUP);};
    auto rentLate = [](RentBook i){return (i.getState() == RENT_LATE);};

    enum {RENTID = 0 ,BOOKID =1, BOOKTITLE = 2, AUTHOR =3, RENTD = 4, EXPD =5, RETURND = 6 , STATE = 7, NOTE = 8};
    std::function<bool(RentBook)> cond = allResult;
    switch (ui->rentHistory_filt->currentIndex())
    {
    case 0:
        cond = allResult;
        break;
    case WAIT_RENT:
        cond = waitRent;
        break;
    case RENT_BACKUP:
        cond = rented;
        break;
    case RENT_FAIL:
        cond = rentFail;
        break;
    case RENT_LATE:
        cond = rentLate;
        break;
    case RENT_NORMAL:
        cond = renting;
        break;
    case RENT_LOST:
        cond = lost;
        break;
    default:
        break;
    }
    for (int i = 0 ; i < tempA.getNumRent() ; ++i)
    {

        RentBook tempR;
        tempR.readData(tempA.getRentList()[i]);
        if (cond(tempR))
        {
           int row = ui->rentHistoryView->rowCount();

           BookType tempB;
           Book tempBook;
           tempB.readData(tempR.getBookID());

           tempB.readData(tempR.getBookTypeID());
           QString state;
           QString note;
           QString returnD;
           if (tempR.getState() == RENT_NORMAL)
              state = "Đang mượn";
           else if (tempR.getState() == WAIT_RENT)
              state = "Đang đợi mượn";
           else if (tempR.getState() == RENT_FAIL)
              state = "Mượn thất bại";
           else if (tempR.getState() == RENT_BACKUP)
              state = "Đã trả";
           else if (tempR.getState() == RENT_LOST)
              state = "Làm mất";
           else if (tempR.getState() == RENT_LATE)
               state = "Trả trễ";
           if (tempR.getFine() != 0)
              note = "Phạt " + QString::number(tempR.getFine());

           if (tempR.getState() == RENT_BACKUP | tempR.getState() == RENT_LATE)
               returnD = QDateToString(tempR.getReturnDate());
           else
               returnD = "";

           QString bID = (tempR.getBookID() == 0 ? "" : QString::number(tempR.getBookID()));

            ui->rentHistoryView->setRowCount(row +1);
            ui->rentHistoryView->setItem(row, RENTID, new QTableWidgetItem(QString::number(tempR.getRentID())));
            ui->rentHistoryView->setItem(row, BOOKID,new QTableWidgetItem(bID));
            ui->rentHistoryView->setItem(row,BOOKTITLE,new QTableWidgetItem(QString(tempB.getName().c_str())));
            ui->rentHistoryView->setItem(row, AUTHOR, new QTableWidgetItem(QString(tempB.getAuthor().c_str())));
            ui->rentHistoryView->setItem(row,RENTD, new QTableWidgetItem(QDateToString(tempR.getRentDate())));
            ui->rentHistoryView->setItem(row,EXPD, new QTableWidgetItem(QDateToString(tempR.getExpDate())));
            ui->rentHistoryView->setItem(row,STATE, new QTableWidgetItem(state));
            ui->rentHistoryView->setItem(row,NOTE, new QTableWidgetItem(note));
            ui->rentHistoryView->setItem(row,RETURND, new QTableWidgetItem(returnD));
        }
    }
    if (tempA.getNumRent() == 0 )
    {
        ui->rentHistoryView->setVisible(false);
        ui->rentHistory_nFoundLabel->setVisible(true);
    }
    else
    {
        ui->rentHistoryView->setVisible(true);
        ui->rentHistory_nFoundLabel->setVisible(false);
        connect(ui->rentHistory_filt, SIGNAL(currentIndexChanged(int)), this, SLOT(rentHistory()));
    }

    ui->implementField->setCurrentIndex(R_RENT_HIS);
}
void Reader::readNotif_beg()
{
    ui->implementField->setCurrentIndex(R_NOTIF);
    enum {ID = 0 , TITLE =1, DATE=2, STATE = 3};
    Notification tempNotif;
    int counter  = 0;
    ui->readNotifView->setRowCount(0);
    long accID = ui->info_accIDLine->text().toLong();
    enum {NSEEN = 1, ALL = 0};
    for (int i = 0 ; i < User::getNNotif() ; ++i)
    {
        tempNotif.readData(i+1);
        if ((tempNotif.getAccID() == accID || tempNotif.getAccID() == 0) && ui->readNotif_filtNotif->currentIndex() == ALL ? 1 : tempNotif.getState() == false)
        {
            ++counter;
            QString state ;
            if (tempNotif.getState() == false)
                state = "Chưa xem";
            else state = "Đã xem";
            ui->readNotifView->setRowCount(counter);
            ui->readNotifView->setItem(counter-1,ID, new QTableWidgetItem(QString::number(tempNotif.getID())));
            ui->readNotifView->setItem(counter-1, TITLE,new QTableWidgetItem(QString(tempNotif.getTitle().c_str())));
            ui->readNotifView->setItem(counter-1, DATE, new QTableWidgetItem(QDateToString(tempNotif.getDateSent())));
            ui->readNotifView->setItem(counter-1,STATE, new QTableWidgetItem(state));
            QPushButton *listB = new QPushButton;
            QHBoxLayout *listLayout = new QHBoxLayout;
            QWidget* listWidget = new QWidget;
            listB->setText("Chi tiết");
            listLayout->addWidget(listB);
            listLayout->setAlignment(Qt::AlignCenter);
            listLayout->setContentsMargins(0, 0, 0, 0);
            listWidget->setLayout(listLayout);
            ui->readNotifView->setCellWidget(counter -1,4,listWidget);
            connect(listB, &QPushButton::clicked, [=]{readNotif_i(ui->readNotifView->item(counter-1,ID)->text().toLong());});
        }
    }
    if (counter != 0)
    {
        ui->readNotifView->setVisible(true);
        ui->readNotif_filtWidget->setVisible(true);
        ui->readNotif_nFoundLabel->setVisible(false);
        connect(ui->readNotif_filtNotif,SIGNAL(currentIndexChanged(int)),this, SLOT(readNotif_beg()));
    }
    else
    {
        ui->readNotifView->setVisible(false);
        ui->readNotif_filtWidget->setVisible(true);
        ui->readNotif_nFoundLabel->setVisible(true);
    }
}

void Reader::readNotif_i(long i)
{
    Notification tempNotif;
    tempNotif.readData(i);
    ui->readNotif_content->setPlainText(QString(tempNotif.getNotif().c_str()));
    ui->readNotif_dateLine->setText(QDateToString(tempNotif.getDateSent()));
    ui->readNotif_idLine->setText(QString::number(tempNotif.getID()));
    ui->readNotif_titleLine->setText(QString(tempNotif.getTitle().c_str()));
    ui->implementField->setCurrentIndex(R_NOTIF_OPT);
    tempNotif.setState(true);
    tempNotif.saveData();
    connect(ui->readNotif_backButton, &QPushButton::clicked, [=]{readNotif_beg();});
}
void Reader::setInfo(long aid)
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
void Reader::logout()
{
    StartProgram *c = new StartProgram();
    c->show();
}
void Reader::info_save()
{
    Account account;
    account.readData(ui->info_accIDLine->text().toLong());
    account.setPassword(ui->info_pwLine->text().toStdString());
    account.saveData();
    ui->info_label->setVisible(true);
    connect(ui->info_pwLine, &QLineEdit::textChanged, [=]{ui->info_label->setVisible(false);});
}
