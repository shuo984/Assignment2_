#include "Librarian.h"
#include "ui_Librarian.h"

enum {L_WELCOME = 0, L_ADD = 1, L_FIND =2, L_EDIT = 3, L_REQUEST = 4, L_ABOUT = 5, L_LOSTBOOK = 6, L_NOTIF = 7, L_INFO = 8};

Librarian::Librarian(const User& x, QWidget *parent) :
    QMainWindow(parent), User(x), ui(new Ui::Librarian)
{
    ui->setupUi(this);
    // Tạo label chưowng trình, đưa về màn hinh chính

    ui->implementField->setCurrentIndex(L_WELCOME);

    // Kết nối các nút lớn với các chức năng chính

    connect(ui->aboutLIBPRO_Button,&QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(L_ABOUT);});
    connect(ui->sendNotif_Button, &QPushButton::clicked, [=]{sendNotif_clear();});
    connect(ui->receiveBook_Button, &QPushButton::clicked,[=]{receiveBook_clear();});
    connect(ui->request_Button, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(L_REQUEST);});
    connect(ui->findBook_Button,&QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(L_FIND);});

    connect(ui->logOut_Button,&QPushButton::clicked, [=]{logout();} );

    // Kết nối các tín hiệu cần thiết, ẩn các widget chưa dùng
    // Thêm sách
    addBook_connect();
    findBook_connect();

    // Tìm sách

    ui->findBookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listBookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Xử lý yêu cầu mượn sách
    request_clear();
    request_beg();
    ui->requestView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->request_errLabel->setVisible(false);
    // Search BID
    request_connect();


    lostBook_clear();
    connect(ui->info_Button, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(L_INFO);});
    ui->listBookView_2->setCurrentIndex(0);

    connect(ui->editBook_saveButton, SIGNAL(clicked(bool)), this, SLOT(editBook_save()));
    connect(ui->editBook_backButton, &QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(L_FIND);});
    connect(ui->editBook_listButton, &QPushButton::clicked, [=]{editBook_list();});
    connect(ui->editBook_listBackButton, &QPushButton::clicked, [=]{ui->listBookView_2->setCurrentIndex(0);});

    connect(ui->sendNotif_allButton,&QRadioButton::toggled,[=]{ui->sendNotif_receiverLine->setDisabled(ui->sendNotif_allButton->isChecked());});
    connect(ui->sendNotif_contentLine, &QTextEdit::textChanged, [=]{ui->sendNotif_sendLabel->setVisible(false);});
    connect(ui->sendNotif_receiverLine, &QLineEdit::textChanged, [=]{ui->sendNotif_sendLabel->setVisible(false);});
    connect(ui->sendNotif_titleLine, &QLineEdit::textChanged, [=]{ui->sendNotif_sendLabel->setVisible(false);});
    connect(ui->sendNotif_sendButton, &QPushButton::clicked, [=]{sendNotif_save();});

    connect(ui->editBook_amountLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_authorLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_summaryLine, &QPlainTextEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_titleLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_typeLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_yearLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_bookIDLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});
    connect(ui->editBook_timesAccessLine,&QLineEdit::textChanged,[=]{ui->editBook_successLabel->setVisible(false);});

    connect(ui->info_pwLine, &QLineEdit::textChanged, [=]{ui->info_label->setVisible(false);});

    ui->lostBook_fineForm->setVisible(false);
    ui->lostBook_nFoundLabel->setVisible(false);
    ui->implementField->setCurrentIndex(0);
    ui->requestStackedWidget->setCurrentIndex(0);
    connect(ui->deleteBook_Button, &QPushButton::clicked, [=]{deleteBookType_connect();});
    ui->sendNotif_sendButton->setEnabled(false);
    connect(ui->sendNotif_receiverLine, &QLineEdit::textChanged,
            [=]{ui->sendNotif_sendButton->setDisabled(ui->sendNotif_receiverLine->text().isEmpty() && !ui->sendNotif_allButton->isChecked());});
}

// Kết nôi với nút thêm sách, nếu thiếu thông tin thì khóa nút đăng kí
void Librarian::addBook_verify()
{
    bool enable = true;
    if (ui->addBook_authorLine->text().isEmpty())
    {
        enable = false;
        ui->addBook_authorLabel->setVisible(true);

    }
    else
    {
        ui->addBook_authorLabel->setVisible(false);
    }

    if (ui->addBook_titleLine->text().isEmpty())
    {
        enable = false;
        ui->addBook_titleLabel->setVisible(true);
    }
    else
    {
        ui->addBook_titleLabel->setVisible(false);
    }

    if ( ui->addBook_yearLine->text().isEmpty())
    {
        enable = false;
        ui->addBook_yearLabel->setVisible(true);
    }
    else
    {
        ui->addBook_yearLabel->setVisible(false);
    }

    if (ui->addBook_typeLine->text().isEmpty())
    {
        enable = false;
        ui->addBook_typeLabel->setVisible(true);
    }
    else
    {
        ui->addBook_typeLabel->setVisible(false);
    }

    ui->addBook_addButton->setEnabled(enable);
    ui->addBook_successLabel->setVisible(false);
}
// Xóa nội dung các hàng trong chức năng thêm sách (sau mỗi lần thêm sách), ẩn widget cần thiết
void Librarian::addBook_clear()
{
    // Ẩn các widget, label chưa cần dùng
    // Các label này là "X" kí hiệu việc nhập ko hợp lệ của hàng tường ứng
    ui->addBook_authorLabel->setVisible(false);
    ui->addBook_titleLabel->setVisible(false);
    ui->addBook_yearLabel->setVisible(false);
    ui->addBook_typeLabel->setVisible(false);
    ui->add1Book_addForm->setVisible(false);
    ui->add1Book_nFoundLabel->setVisible(false);
    ui->add1Book_addLabel->setVisible(false);

    // Làm trống các hàng trong chức năng đó

    ui->addBook_authorLine->clear();
    ui->addBook_titleLine->clear();
    ui->addBook_typeLine->clear();
    ui->addBook_yearLine->clear();


    // Mặc định khóa nút thêm sách

    ui->addBook_addButton->setDisabled(true);
    ui->addBook_successLabel->setVisible(false);
    ui->addBook_summaryText->setEnabled(true);

    ui->addBook_BTypeID->setText(QString::number(getNBookType() + 1));
}
// Lưu thông tin sách, slot này được kết nối với nút thêm sách (sau khi đã điền đầy đủ thông tin), kết thúc thêm sách
void Librarian::addBook_save()
{
    // Lấy thông tin từ các hàng người dùng nhập vào

    std::string summa = ui->addBook_summaryText->document()->toPlainText().toStdString();
    std::string title = ui->addBook_titleLine->text().toStdString();
    std::string author = ui->addBook_authorLine->text().toStdString();
    std::string type = ui->addBook_typeLine->text().toStdString();
    int year = ui->addBook_yearLine->text().toLong();

    // Tạo sách với các thông tin đó

    BookType newB(getNBookType() +1,title,author,type,summa,year,0,0,0,0);
    newB.saveData();
    setNBookType(getNBookType() + 1);

    // Gửi thông báo sách mới đến đọc giả

    std::string notifTitle = "Sách mới về";
    std::string notifContent = "Chào bạn đọc\n Thư viện vừa thêm sách " + title  + " mời bạn đón đọc.";
    Notification newNotif(getNNotif()+1,0,notifTitle,notifContent,QDate::currentDate(),false);
    newNotif.saveData();
    setNNotif(getNNotif() + 1);
    ui->addBook_successLabel->setVisible(true);
    ui->addBook_BTypeID->setText(QString::number(getNBookType() +1));

}

// Slot kết nối với nút tìm sách trong chức năng tìm sách
void Librarian::findBook_find()
{
    BookType tempB;
    int counter = 0;
    ui->findBookView->setRowCount(0);
    enum {BOOKID=0, BOOK_TITLE = 1, BOOK_AUTHOR =2, BOOK_YEAR = 3, BOOK_AMOUNT = 4, BOOK_AV = 5, BOOK_FREE = 6, BOOK_TIMES = 7, BOOK_DATE =8};

    std::string findKey = ui->findBook_findLine->text().toStdString();

    // Điền các thông tin thỏa mãn vào bảng

    for (int i = 0 ; i < getNBookType() ; ++i)
    {
        tempB.readData(i +1);
        if (tempB.getBookID() != 0)
        {
            if (tempB.getAuthor().find(findKey) != std::string::npos
                    || tempB.getName().find(findKey) != std::string::npos
                    || tempB.getSummary().find(findKey) !=std::string::npos)
            {
                // Điền thông tin

                ui->findBookView->setRowCount(ui->findBookView->rowCount() + 1);
                ui->findBookView->setItem(counter,BOOKID, new QTableWidgetItem(QString::number(tempB.getBookID())));
                ui->findBookView->setItem(counter, BOOK_TITLE, new QTableWidgetItem(QString(tempB.getName().c_str())));
                ui->findBookView->setItem(counter,BOOK_AUTHOR, new QTableWidgetItem(QString(tempB.getAuthor().c_str())));
                ui->findBookView->setItem(counter,BOOK_YEAR, new QTableWidgetItem(QString::number(tempB.getYear())));
                ui->findBookView->setItem(counter, BOOK_AMOUNT, new QTableWidgetItem(QString::number(tempB.getAmount())));
                ui->findBookView->setItem(counter, BOOK_AV, new QTableWidgetItem(QString::number(tempB.getAvailable())));
                ui->findBookView->setItem(counter, BOOK_TIMES, new QTableWidgetItem(QString::number(tempB.getTimeAccess())));
                ui->findBookView->setItem(counter, BOOK_FREE, new QTableWidgetItem(QString::number(tempB.getNFree())));


                // Tạo nút "chi tiết" ứng với từng hàng (từng cuốn sách)

                QPushButton *listB = new QPushButton;
                QHBoxLayout *listLayout = new QHBoxLayout;
                QWidget* listWidget = new QWidget;
                listB->setText("Chi tiết");
                listLayout->addWidget(listB);
                listLayout->setAlignment(Qt::AlignCenter);
                listLayout->setContentsMargins(0, 0, 0, 0);
                listWidget->setLayout(listLayout);
                ui->findBookView->setCellWidget(counter,8,listWidget);
                connect(listB, &QPushButton::clicked,
                        [=]{editBook_beg(ui->findBookView->item(counter ,BOOKID)->text().toLong());ui->implementField->setCurrentIndex(L_EDIT);
                            ui->listBookView_2->setCurrentIndex(0);});
                ++counter;
            }
        }
    }

    if (counter != 0)     // Nếu điền thành công
    {
        ui->findBookView->setVisible(true);     // Ẩn bảng thông tin
        ui->findBook_findLabel->setVisible(false);  // Hiện ra label thông báo không tìm thấy
    }
    else        // Nếu chưa điền (không có thông tin tìm thấy)
    {
        ui->findBookView->setVisible(false);    // Hiện bảng thông tin
        ui->findBook_findLabel->setVisible(true);       //Ẩn label thông báo không tìm thấy
    }
}

void Librarian::add1Book_verify()
{
    ui->add1Book_findButton->setEnabled(ui->add1Book_BTypeLine->text().toLong() > 0 &&  ui->add1Book_BTypeLine->text().toLong() < 10000);
}
void Librarian::addBook_connect()
{
    addBook_clear();
    connect(ui->addBook_Button, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(L_ADD); addBook_clear();});
    connect(ui->addBook_authorLine, SIGNAL(textChanged(QString)), this, SLOT(addBook_verify()));
    connect(ui->addBook_titleLine, SIGNAL(textChanged(QString)), this, SLOT(addBook_verify()));
    connect(ui->addBook_typeLine, SIGNAL(textChanged(QString)), this, SLOT(addBook_verify()));
    connect(ui->addBook_yearLine, SIGNAL(textChanged(QString)), this, SLOT(addBook_verify()));
    connect(ui->addBook_addButton, SIGNAL(clicked(bool)), this, SLOT(addBook_save()));
    connect(ui->addBook_backButton, &QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(0);addBook_clear();});

    connect(ui->add1Book_BTypeLine, &QLineEdit::textChanged, [=]{add1Book_verify();});
    connect(ui->add1Book_findButton, &QPushButton::clicked, [=]{add1Book_find();});
    connect(ui->add1Book_addButton, &QPushButton::clicked, [=]{add1Book_save();ui->add1Book_addLabel->setVisible(true);});
    connect(ui->add1Book_BTypeLine, &QLineEdit::textChanged, [=]{ui->add1Book_addForm->setVisible(false);
        ui->add1Book_nFoundLabel->setVisible(false);
        ui->add1Book_addLabel->setVisible(false);});

}

void Librarian::add1Book_find()
{
    BookType tempBT;
    tempBT.readData(ui->add1Book_BTypeLine->text().toLong());
    if (tempBT.getBookID() != 0)
    {
        ui->add1Book_authorLine->setText(QString(tempBT.getAuthor().c_str()));
        ui->add1Book_titleLine->setText(QString(tempBT.getName().c_str()));
        ui->add1Book_BTypeLine->setText(QString::number(tempBT.getBookID()));
        ui->add1Book_BIDLine->setText(QString::number(getNBook()+1));
        ui->add1Book_addForm->setVisible(true);
        ui->add1Book_nFoundLabel->setVisible(false);
    }
    else
    {
        ui->add1Book_nFoundLabel->setVisible(true);
        ui->add1Book_addForm->setVisible(false);
    }
}

void Librarian::add1Book_save()
{

    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};
    BookType tempBT;
    tempBT.readData(ui->add1Book_BTypeLine->text().toLong());
    Book newB(ui->add1Book_BTypeLine->text().toLong(),
              ui->add1Book_BIDLine->text().toLong(),
              QDate::currentDate(),
              B_AVAIL);
    newB.saveData();
    setNBook(getNBook() + 1);
    tempBT.setAmount(tempBT.getAmount() + 1);
    tempBT.setAvailable(tempBT.getAvailable() + 1);
    tempBT.setNFree(tempBT.getNFree() + 1);
    tempBT.saveData();
    ui->add1Book_BIDLine->setText(QString::number(getNBook() + 1));
}

void Librarian::findBook_clear()
{
    ui->findBookView->setRowCount(0);
    ui->findBookView->setVisible(false);
    ui->findBook_findLabel->setVisible(false);
    ui->searchBookID_Form->setVisible(false);
    ui->searchBID_nFoundLabel->setVisible(false);
}

void Librarian::findBook_connect()
{
    findBook_clear();
    connect(ui->findBook_findLine, &QLineEdit::textChanged, [=]{ui->findBook_findLabel->setVisible(false);});
    connect(ui->findBook_findButton, SIGNAL(clicked(bool)),this, SLOT(findBook_find()));
    connect(ui->searchBID_sButton,&QPushButton::clicked,[=]{searchBID();});

    connect(ui->searchBID_sLine, &QLineEdit::textChanged,
            [=]{;ui->searchBID_sButton->setEnabled((ui->searchBID_sLine->text().toLong() <10000 && ui->searchBID_sLine->text().toLong() >0));});
}

void Librarian::request_beg()
{
    ui->requestStackedWidget->setCurrentIndex(0);
    ui->requestView->setRowCount(0);
    enum { RENT_ID = 0 , BOOK_ID =1, BOOK_TITLE =2, ACC_ID = 3, NAME = 4, STATE = 5, FINE =6 };
    int counter = 0;

    // Tạo các đổi tượng để ánh xạ lấy thông tin cần thiết điền vào bảng thông tin

    RentBook tempR;
    BookType tempB;
    Account tempA;
    User tempU;

    // Điền các bản ghi mượn có trạng thái "WAIT_RENT" vào bảng

    for (int i = 0 ; i < User::getFNumRent() ; ++i)
    {
        tempR.readData(i+1);
        if (tempR.getState() == WAIT_RENT)
        {
            ++counter;
            tempB.readData(tempR.getBookTypeID());
            tempA.readData(tempR.getAccID());
            tempU.readUser(tempA.getLibID());

            ui->requestView->setRowCount(counter);
            QString state;
            if (tempR.getState() == WAIT_RENT)
                state = "Đợi mượn";
            ui->requestView->setItem(counter-1,RENT_ID,new QTableWidgetItem(QString::number(tempR.getRentID())));
            ui->requestView->setItem(counter-1,BOOK_ID,new QTableWidgetItem(QString::number(tempR.getBookTypeID())));
            ui->requestView->setItem(counter-1, BOOK_TITLE, new QTableWidgetItem(QString(tempB.getName().c_str())));
            ui->requestView->setItem(counter-1,ACC_ID,new QTableWidgetItem(QString::number(tempR.getAccID())));
            ui->requestView->setItem(counter-1,NAME, new QTableWidgetItem(QString(tempU.getFullName().c_str())));
            ui->requestView->setItem(counter-1,STATE, new QTableWidgetItem(state));
        }
    }

    if (counter!=0)     // Nếu có thông tin
    {
        ui->requestView->setVisible(true);
        ui->request_Label->setVisible(false);
        for (int i = 0 ; i < counter ; ++i)
        {
            QPushButton *listB = new QPushButton;
            QPushButton *listB2 = new QPushButton;
            QHBoxLayout *listLayout = new QHBoxLayout;
            QWidget* listWidget = new QWidget;
            listB->setText("Chấp nhận");
            listB2->setText("Từ chối");
            listLayout->addWidget(listB);
            listLayout->addWidget(listB2);
            listLayout->setAlignment(Qt::AlignCenter);
            listLayout->setContentsMargins(0, 0, 0, 0);
            listWidget->setLayout(listLayout);
            ui->requestView->setCellWidget(i,6,listWidget);
            ui->requestStackedWidget->setCurrentIndex(1);
            ui->request_succLabel->setVisible(false);
            connect(listB, &QPushButton::clicked, [=]{request_opt(i);request_beg();});
            connect(listB2, &QPushButton::clicked, [=]{request_cancel_i(i);ui->requestView->removeRow(i);request_beg();});
        }

    }
    else    // Nếu không có thông tin
    {
        ui->requestView->setVisible(false);
        ui->request_Label->setVisible(true);
    }
}
void Librarian::request_connect()
{
    connect(ui->request_bookIDLine, &QLineEdit::textChanged,
            [=]{ui->request_errLabel->setVisible(false);
                ui->request_succLabel->setVisible(false);});
    connect(ui->request_bookIDLine, &QLineEdit::textChanged,
            [=]{ui->request_Button->setDisabled(ui->request_bookIDLine->text().isEmpty());});
    connect(ui->request_backButton, &QPushButton::clicked, [=]{request_beg();ui->requestStackedWidget->setCurrentIndex(0);});
}

// Làm mới lại chức năng request

void Librarian::request_clear()
{
    ui->requestView->setVisible(false);
    ui->request_Label->setVisible(false);
    ui->requestView->setRowCount(0);
}

// Chấp nhận yêu cầu mượn sách, kết nối với hàng i trong bảng dữ liệu

void Librarian::request_opt(int i)
{
    enum { RENT_ID = 0 , BOOK_ID =1, BOOK_TITLE =2, ACC_ID = 3, NAME = 4, STATE = 5 };
    // Chuyển trang
    // Điền thông tin vào bảng
    // Kết nối nút xác thực với tín hiệu lưu lại bảng ghi mượn
    // Cho quyển sách mượn về trạng thái đang được mượn
    // Giảm số sách có sẵn xuống
    // Ok
    ui->requestStackedWidget->setCurrentIndex(1);
    RentBook tempR;
    tempR.readData(ui->requestView->item(i,RENT_ID)->text().toLong());
    ui->request_rentIDLine->setText(QString::number(ui->requestView->item(i,RENT_ID)->text().toLong()));
    ui->request_titleLine->setText(ui->requestView->item(i,BOOK_TITLE)->text());
    ui->request_nameLine->setText(ui->requestView->item(i,NAME)->text());
    ui->request_accIDLine->setText(QString::number(ui->requestView->item(i,ACC_ID)->text().toLong()));
    ui->request_bookTypeIDLine->setText(QString::number(ui->requestView->item(i,BOOK_ID)->text().toLong()));
    ui->request_confirmButton->setEnabled(true);
    connect(ui->request_confirmButton, &QPushButton::clicked, [=]{request_save(i);});
    ui->request_expDLine->setMinimumDate(tempR.getRentDate());
    ui->request_rentDLine->setMinimumDate(tempR.getRentDate());
}
void Librarian::request_save(int i)
{
    ui->request_succLabel->setVisible(false);
    ui->request_errLabel->setVisible(false);
    ui->request_confirmButton->setEnabled(true);

        Book tempB;
        tempB.readData(ui->request_bookIDLine->text().toLong());
        qDebug() << ui->request_bookIDLine->text().toLong();
        qDebug() << ui->request_bookTypeIDLine->text().toLong();
        qDebug() << tempB.getTypeBook();
        qDebug() << tempB.getState();
        qDebug() << B_AVAIL;
        if ((tempB.getBookID() != 0) && (tempB.getTypeBook() == ui->request_bookTypeIDLine->text().toLong()) && (tempB.getState() == B_AVAIL))
        {
            ui->request_errLabel->setVisible(false);
            // Thay đổi thông tin bản ghi mượn
            RentBook tempRent;
            tempRent.readData(ui->request_rentIDLine->text().toLong());
            tempRent.setState(RENT_NORMAL);
            tempRent.setRentDate(ui->request_expDLine->date());
            tempRent.setExpireDate(ui->request_rentDLine->date());
            tempRent.setBookID(ui->request_bookIDLine->text().toLong());
            tempRent.saveData();
            //Giảm số lượng sách sẵn có xuống
            BookType bookType;
            bookType.readData(tempRent.getBookTypeID());
            bookType.setAvailable(bookType.getAvailable() - 1);
            bookType.saveData();
            //Thay đổi trạng thái cuốn sách được cho mượn
            Book tempBook;
            tempBook.readData(tempRent.getBookID());
            tempBook.setState(B_RENT);
            tempBook.setRentID(tempRent.getRentID());
            tempBook.saveData();
            ui->requestView->removeRow(i);
            ui->request_succLabel->setVisible(true);
            ui->request_confirmButton->setEnabled(false);
            ui->request_errLabel->setVisible(false);
            qDebug() << "Success";
            disconnect(ui->request_confirmButton, SIGNAL(clicked(bool)),0,0);
        }
        else
        {
            ui->request_errLabel->setVisible(true);
            ui->request_succLabel->setVisible(false);
            qDebug() << "Fail";

        }



}

// Từ chối yêu cầu mượn sách, kết nối với hàng i trong bảng dữ liệu

void Librarian::request_cancel_i(int i)
{
    long rentID = ui->requestView->item(i,0)->text().toLong();
    RentBook tempR;
    tempR.readData(rentID);
    if (tempR.getState() == WAIT_RENT)
    {
        tempR.setState(RENT_FAIL);
        BookType bookType;
        bookType.readData(tempR.getBookTypeID());
        bookType.setNFree(bookType.getNFree() + 1);
        bookType.saveData();
    }
    tempR.saveData();
}

// Sửa thông tin sách, chức năng này liên kết trực tiếp với chức năng tìm kiếm nên không cần xác thực gì cả
// Kết nối với nút chi tiết từ chức năng tìm sách

void Librarian::editBook_beg(long i)
{
    BookType tempB;
    tempB.readData(i);
    ui->editBook_successLabel->setVisible(false);
    ui->editBook_amountLine->setText(QString::number(tempB.getAmount()));
    ui->editBook_authorLine->setText(QString(tempB.getAuthor().c_str()));
    ui->editBook_summaryLine->setPlainText(QString(tempB.getSummary().c_str()));
    ui->editBook_titleLine->setText(QString(tempB.getName().c_str()));
    ui->editBook_typeLine->setText(QString(tempB.getType().c_str()));
    ui->editBook_yearLine->setText(QString::number(tempB.getYear()));
    ui->editBook_bookIDLine->setText(QString::number(tempB.getBookID()));
    ui->editBook_timesAccessLine->setText(QString::number(tempB.getTimeAccess()));
    ui->editBook_avLine->setText(QString::number(tempB.getAvailable()));
    ui->editBook_nFree->setText(QString::number(tempB.getNFree()));




    ui->editBook_listButton->setEnabled(tempB.getAmount() > 0);
}

// Lưu sách khi nhận được tín hiệu từ chức năng sửa thông tin sách

void Librarian::editBook_save()
{
    // Đọc thông tin từ các hàng, lưu lại thông tin sách

    long amount = ui->editBook_amountLine->text().toLong();
    std::string author = ui->editBook_authorLine->text().toStdString();
    std::string summary = ui->editBook_summaryLine->document()->toPlainText().toStdString();
    std::string title = ui->editBook_titleLine->text().toStdString();
    std::string type = ui->editBook_typeLine->text().toStdString();
    int year = ui->editBook_yearLine->text().toLong();
    long id = ui->editBook_bookIDLine->text().toLong();
    long times = ui->editBook_timesAccessLine->text().toLong();
    long av = ui->editBook_avLine->text().toLong();
    BookType tempB;
    tempB.readData(id);
    tempB.setAmount(amount);
    tempB.setAuthor(author);
    tempB.setSummary(summary);
    tempB.setTitle(title);
    tempB.setType(type);
    tempB.setYear(year);
    tempB.setTimesAcess(times);
    tempB.setAvailable(av);
    tempB.saveData();

    // Hiện label thông báo đã thêm sách

    ui->editBook_successLabel->setVisible(true);

    // Kết nối tín hiệu thay đổi thông tin tuừ tất cả các hàng, ẩn label thông báo thành công ngay khi có thông tin tháy đổi



}

// Kết nối với nút tìm kiếm trong chức năng giải quyết mất sách
// CHỉ tìm những bản ghi mượn sách có trạng thái là đang mượn, nếu không thì thông báo không tìm thấy

void Librarian::lostBook_find()
{
    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};
    long fKey  = ui->lostBook_findLine->text().toLong();        // Đọc từ ô tìm kiếm

    // Tạo đối tượng ánh xạ qua lại lấy thông tin
    ui->lostBook_fineButton->setEnabled(true);
    RentBook tempRent;
    BookType bookType;
    Account tempA;
    User tempUser;
    Book tempB;
    tempB.readData(fKey);
    qDebug() << "XXX";
    if (tempB.getBookID() != 0 && tempB.getState() == B_RENT)   // Đọc mã sách từ ô tìm kiếm, nếu có thông tin
    {

        bookType.readData(tempB.getTypeBook());
        for (int i = 0 ; i < getFNumRent() ; ++i)   // Chắc chắn tồn tại mã mượn sách phù hợp
        {
            tempRent.readData(i+1);
            if (tempRent.getBookID() == fKey)
                break;
        }

        tempA.readData(tempRent.getAccID());
        tempUser.readUser(tempA.getLibID());

        // Ánh xạ xong bắt đầu điền thông tin vào bảng

        ui->lostBook_bookIDLine->setText(QString::number(tempRent.getBookID()));
        ui->lostBook_accIDLine->setText(QString::number(tempA.getAccountID()));
        ui->lostBook_bookTitleLine->setText(QString(bookType.getName().c_str()));
        ui->lostBook_nameLine->setText(QString(tempUser.getFullName().c_str()));
        ui->lostBook_rentIdLine->setText(QString::number(tempRent.getRentID()));
        ui->lostBook_BTypeID->setText(QString::number(tempB.getTypeBook()));

        // Kết nối 2 nut với tín hiệu tương ứng
        connect(ui->lostBook_backButton,&QPushButton::clicked, [=]{ui->implementField->setCurrentIndex(0);});
        connect(ui->lostBook_fineButton,&QPushButton::clicked, [=]{lostBook_save();});

        // Hiển thị form lên, ẩn thông báo không tìm thấy
        ui->lostBook_fineForm->setVisible(true);
        ui->lostBook_nFoundLabel->setVisible(false);
    }
    else
    {
        // Ẩn bảng thông tin, hiện thông báo không tìm thấy
        ui->lostBook_fineForm->setVisible(false);
        ui->lostBook_nFoundLabel->setVisible(true);
    }
}

// Tạo thông báo mới

void Librarian::sendNotif_save()
{

    long accID = (ui->sendNotif_allButton->isChecked() ? 0 : ui->sendNotif_receiverLine->text().toLong());
    std::string title = ui->sendNotif_titleLine->text().toStdString();
    std::string content = ui->sendNotif_contentLine->toPlainText().toStdString();
    Notification newNotif(getNNotif() + 1,accID,title,content, QDate::currentDate(),false);
    setNNotif(getNNotif() + 1);
    newNotif.saveData();
    ui->sendNotif_sendLabel->setVisible(true);
}

// Làm mới lại chức năng gửi thông báo (ẩn , xóa ...)

void Librarian::sendNotif_clear()
{
    ui->sendNotif_sendLabel->setVisible(false);
    ui->sendNotif_allButton->setChecked(false);
    ui->sendNotif_contentLine->clear();
    ui->sendNotif_receiverLine->clear();
    ui->sendNotif_titleLine->clear();
    ui->implementField->setCurrentIndex(L_NOTIF);


}

// Làm mới lại chức năng giải quyết mất sách (ẩn , xóa ...)

void Librarian::lostBook_clear()
{
    ui->lostBook_fineForm->setVisible(false);
    ui->lostBook_nFoundLabel->setVisible(false);
    ui->lostBook_bookIDLine->clear();
    ui->lostBook_bookTitleLine->clear();
    ui->lostBook_findLine->clear();
    ui->lostBook_nameLine->clear();
    ui->lostBook_rentIdLine->clear();
    ui->lostBook_accIDLine->clear();
    ui->lostBook_noteLabel->setVisible(false);
    ui->implementField->setCurrentIndex(L_LOSTBOOK);
    connect(ui->lostBook_findButton, &QPushButton::clicked,[=]{lostBook_find();});

}

// Hoàn thành giải quyết mất sách, lưu thông tin và gửi thông tin

void Librarian::lostBook_save()
{
    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};
    long fine = ui->lostBook_fineLine->text().toLong();     // Tiền phạt
    long accID = ui->lostBook_accIDLine->text().toLong();   // Để gửi thông báo
    std::string booktit = ui->lostBook_bookTitleLine->text().toStdString();
    std::string name = ui->lostBook_nameLine->text().toStdString();
    RentBook tempRent;
    BookType bookType;
    Book tempB;


    bookType.readData(ui->lostBook_BTypeID->text().toLong());
    bookType.setAmount(bookType.getAmount() - 1);
    bookType.saveData();

    tempRent.readData(ui->lostBook_rentIdLine->text().toLong());
    tempRent.setState(RENT_LOST);
    tempRent.setFine(fine);
    tempRent.saveData();

    tempB.readData(tempRent.getBookID());
    tempB.setState(B_LOST);
    tempB.saveData();
    ui->lostBook_noteLabel->setVisible(true);
    std::string tit = "Phạt vì mất sách";
    std::string content = "Chào " + name + "\nBạn bị phạt " + std::to_string(fine) + "VND vì làm mất sách "
            + booktit + "\nVui lòng thanh toán đúng hạn.";
    Notification newNotif(getNNotif() + 1,accID,tit,content,QDate::currentDate(),false);
    setNNotif(getNNotif() + 1);
    newNotif.saveData();
    ui->lostBook_fineButton->setEnabled(false);
}

// Làm mới chức năng ghi nhận trả sách (chức năng làm mới nghĩa là xóa thông tin cũ từ các hàng, ẩn label..)
// Chức năng làm mới hỗ trợ các chức năng mà phải nhập nhiều thông tin

void Librarian::receiveBook_clear()
{
    ui->receiveBook_Form_3->setVisible(false);
    ui->receiveBook_nFoundButton_2->setVisible(false);
    ui->implementField->setCurrentIndex(L_LOSTBOOK);
    connect(ui->receiveBook_findButton_2,&QPushButton::clicked, [=]{receiveBook_find();});
    ui->receiveBook_successLabel_2->setVisible(false);
    ui->receiveBook_lateButton_2->setChecked(false);
    connect(ui->receiveBook_lateButton_2,&QRadioButton::toggled,[=]{ui->receiveBook_fineWidget_2->setVisible(ui->receiveBook_lateButton_2->isChecked());});
    ui->receiveBook_fineWidget_2->setVisible(false);
}

// Tìm kiếm bản ghi phù hợp

void Librarian::receiveBook_find()
{
    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};
    ui->receiveBook_confirmButton_2->setEnabled(true);
    long BID = ui->receiveBook_findLine_2->text().toLong();
    Book tempB;
    tempB.readData(BID);

    if (tempB.getBookID() == 0 || tempB.getState() != B_RENT)      // Không tìm thấy
    {
        ui->receiveBook_Form_3->setVisible(false);
        ui->receiveBook_nFoundButton_2->setVisible(true);
        ui->request_Form->setVisible(false);
    }
    else        // TÌm thấy bản ghi thõa
    {
        qDebug() << "Found" ;
        // Tạo đối tượng, ánh xạ lấy thông tin điền vào bảng thông tin chi tiết
        BookType bookType;
        RentBook tempRent;
        Account tempA;
        User tempUser;
        for (int i = 0 ; i < getFNumRent() ; ++i)
        {
            tempRent.readData(i+1);
            if (tempRent.getBookID() == tempB.getBookID())
                break;  // Tìm thấy bản ghi mượn phù hợp

        }
        tempA.readData(tempRent.getAccID());
        tempUser.readUser(tempA.getLibID());
        bookType.readData(tempRent.getBookTypeID());

        //ĐIền thông tin vào mẫu

        ui->receiveBook_nFoundButton_2->setVisible(false);
        ui->receiveBook_accIDLine_2->setText(QString::number(tempRent.getAccID()));
        ui->receiveBook_bookIDLine_2->setText(QString::number(tempRent.getBookID()));
        ui->receiveBook_bookTitleLine_2->setText(QString(bookType.getName().c_str()));
        ui->receiveBook_expDLine_2->setText(QDateToString(tempRent.getExpDate()));
        ui->receiveBook_nameLine_2->setText(QString(tempUser.getFullName().c_str()));
        ui->receiveBook_rentDLine_2->setText(QDateToString(tempRent.getRentDate()));
        ui->receiveBook_rentIDLine_2->setText(QString::number(tempRent.getRentID()));
        ui->receiveBook_Form_3->setVisible(true);
        ui->receiveBook_returnDLine_2->setMinimumDate(tempRent.getRentDate());
        ui->request_Form->setVisible(true);
        // Kết nối 2 quay lại và xác nhận, quay lại thì đưa về trang chào mừng (index 0)
        // Xác nhận thì chuyển sang slot khác, lưu thông tin tương ứng

        connect(ui->receiveBook_backButton_2,&QPushButton::clicked,[=]{ui->implementField->setCurrentIndex(0);});
        connect(ui->receiveBook_confirmButton_2, SIGNAL(clicked(bool)),this, SLOT(receiveBook_save()), Qt::UniqueConnection);
    }
}

// Lưu thông tin nhận sách

void Librarian::receiveBook_save()
{

    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};

    RentBook tempRent;
    BookType bookType;
    Account tempA;
    User tempUser;
    Book tempB;

    tempRent.readData(ui->receiveBook_rentIDLine_2->text().toLong());
    tempA.readData(tempRent.getAccID());
    bookType.readData(tempRent.getBookTypeID());
    tempB.readData(tempRent.getBookID());

    if (ui->receiveBook_lateButton_2->isChecked())    // Nếu nút trễ hạn được bấm
    {
        tempRent.setState(RENT_LATE);       //"Đã trả trễ hạn"
        tempRent.setFine(ui->receiveBook_fineLine_2->text().toLong());    // Thêm tiền phạt

        // Gửa thông báo đến người dùng

        std::string tit = "Bị phạt vì trả sách trễ hạn";
        std::string cont = "Chào " + tempUser.getFullName() +",\nBạn bị phat"
                + std::to_string(ui->receiveBook_fineLine_2->text().toLong())
                + " vì trả sách trễ hạn.\nVui lòng thanh toán tiền phạt đúng hạn.";
        Notification newNotif(getNNotif() + 1, tempA.getAccountID(),tit,cont,QDate::currentDate(),false);
        newNotif.saveData();
        setNNotif(getNNotif() + 1);
    }
    else        // Nếu không trễ hạn
    {
        tempRent.setState(RENT_BACKUP);
        tempRent.setFine(0);
    }

    // Lưu bản ghi lại


    bookType.setAvailable(bookType.getAvailable() + 1);
    bookType.saveData();
    tempB.setState(B_AVAIL);
    tempB.saveData();
    tempRent.saveData();
    ui->receiveBook_successLabel_2->setVisible(true);
    ui->receiveBook_confirmButton_2->setEnabled(false);


}
void Librarian::logout()
{
    close();
    StartProgram *c = new StartProgram();
    c->show();
}
void Librarian::searchBID()
{
    enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};
    Book tempB;
    tempB.readData(ui->searchBID_sLine->text().toLong());
    if (tempB.getBookID() != 0)
    {
        BookType bookType;
        bookType.readData(tempB.getTypeBook());
        ui->searchBID_nFoundLabel->setVisible(false);
        ui->searchBID_author->setText(QString(bookType.getAuthor().c_str()));
        ui->searchBID_BTLine->setText(QString::number(bookType.getBookID()));
        ui->searchBID_titleLine->setText(QString(bookType.getName().c_str()));
        ui->searchBID_yLine->setText(QString::number(bookType.getYear()));
        ui->searchBID_addDLine->setText(QDateToString(tempB.getAddDate()));
        ui->searchBID_typeLine->setText(QString(bookType.getType().c_str()));
        QString state;
        if (tempB.getState() == B_AVAIL)
            state = "Có sẵn";
        else if (tempB.getState() == B_RENT)
            state = "Đang được mượn";
        else if (tempB.getState() == B_LOST)
            state = "Bị mất";
        ui->searchBID_stateLine->setText(state);
        ui->searchBookID_Form->setVisible(true);
    }
    else
    {
        ui->searchBID_nFoundLabel->setVisible(true);
        ui->searchBookID_Form->setVisible(false);
        connect(ui->searchBID_sLine, &QLineEdit::textChanged, [=]{ui->searchBID_nFoundLabel->setVisible(false);});
    }
}

void Librarian::searchBID_verify()
{

}
void Librarian::setInfo(long aid)
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
void Librarian::editBook_list()
{
    Book book;
    ui->listBookView->setRowCount(0);
    int counter = 0;
    enum {B_TITLE = 0, B_AUTHOR = 1, B_ID = 2, B_STATE = 3, B_ACCID = 4, B_NAME_RENT= 5 , ADD_DATE = 6};
    for (int i = 0 ; i < getNBook() ; ++i)
    {
        book.readData(i+1);
        if (book.getTypeBook() == ui->editBook_bookIDLine->text().toLong())
        {
            ++counter;
            BookType bookType;
            User user;
            RentBook rentBook;
            rentBook.readData(book.getRentID());
            bookType.readData(book.getTypeBook());
            ui->listBookView->setRowCount(counter);
            ui->listBookView->setItem(counter-1,B_TITLE, new QTableWidgetItem(QString::fromStdString(bookType.getName())));
            ui->listBookView->setItem(counter-1, B_AUTHOR, new QTableWidgetItem(QString::fromStdString(bookType.getAuthor())));
            ui->listBookView->setItem(counter-1, B_ID, new QTableWidgetItem(QString::number(book.getBookID())));
            QString state ;
            if (book.getState() == B_RENT)
                state = "Đang mượn";
            else if (book.getState()== B_LOST)
                state = "Bị mất";
            else
                state = "Có sẵn";
            ui->listBookView->setItem(counter - 1, B_STATE, new QTableWidgetItem(state));
            if (book.getState() == B_RENT)
            {
                Account account;
                account.readData(rentBook.getAccID());
                user.readUser(account.getLibID());
                ui->listBookView->setItem(counter-1,B_ACCID, new QTableWidgetItem(QString::number(rentBook.getAccID())));
                ui->listBookView->setItem(counter-1,B_NAME_RENT, new QTableWidgetItem(QString::fromStdString(user.getFullName())));
            }
            ui->listBookView->setItem(counter-1, ADD_DATE, new QTableWidgetItem((QDateToString(book.getAddDate()))));
            QPushButton *listB = new QPushButton;
            QHBoxLayout *listLayout = new QHBoxLayout;
            QWidget* listWidget = new QWidget;
            listB->setText("Xóa");
            listLayout->addWidget(listB);
            listLayout->setAlignment(Qt::AlignCenter);
            listLayout->setContentsMargins(0, 0, 0, 0);
            listWidget->setLayout(listLayout);
            ui->listBookView->setCellWidget(counter -1,7,listWidget);
            connect(listB, &QPushButton::clicked,
                    [=]{deleteBook(ui->listBookView->item(counter-1,2)->text().toLong()) ; ui->listBookView->removeRow(counter-1);editBook_list();});
        }
    }
    ui->listBookView_2->setCurrentIndex(1);
    connect(ui->editBook_listBackButton, &QPushButton::clicked, [=]{ui->listBookView_2->setCurrentIndex(0);});
}
void Librarian::info_save()
{
    Account account;
    account.readData(ui->info_accIDLine->text().toLong());
    account.setPassword(ui->info_pwLine->text().toStdString());
    account.saveData();
    ui->info_label->setVisible(true);

}
void Librarian::deleteBook(long id)
{
    Book book;
    book.readData(id);
    qDebug() << book.getBookID();
    BookType bookType;
    bookType.readData(book.getTypeBook());
    Book blankBook;
    blankBook.saveData(id);

    if (book.getState() == B_AVAIL)
        bookType.setAvailable(bookType.getAvailable() - 1);

    bookType.setAmount(bookType.getAmount() - 1);
    bookType.setNFree(bookType.getNFree() - 1);
    bookType.saveData();
    blankBook.saveData(id);
}

void Librarian::deleteBookType(long id)  // Xóa 1 loại sách
{
    BookType blankB;
    Book book;
    Book blankBook;
    blankB.saveData(id);
    // Xóa hết luôn từng cuốn
    for (int i = 0 ; i < getNBook() ; ++i)
    {
        book.readData(i+1);
        if (book.getTypeBook() == id)
            blankBook.saveData(book.getBookID());
    }
}
void Librarian::deleteBookType_connect()
{
    QMessageBox message;
    message.setWindowTitle("Xóa sách");
    message.setText("Xóa sách thành công");
    message.exec();
    deleteBookType(ui->editBook_bookIDLine->text().toLong());
    ui->listBookView_2->setCurrentIndex(0);
}
Librarian::~Librarian()
{
    delete ui;
}
