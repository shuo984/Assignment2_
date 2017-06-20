#ifndef READER_H
#define READER_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <string>
#include <vector>
#include <QInputDialog>
#include <functional>
#include "StartProgram.h"
#include "BookType.h"
#include "User.h"

namespace Ui {
class Reader;
}

class Reader : public QMainWindow, public User
{
    Q_OBJECT

public:
    explicit Reader(const User& = {}, QWidget *parent = 0);
    ~Reader();
     void setInfo(long);                // Gán thông tin người dùng lúc đăng nhập vào chương trình
private slots:
    void findBook_find();               // Bắt đầu tìm kiếm khi nút tìm kiếm được bấm
    void findBook_opt(long);            // Lưạ chọn với cuốn sách được tìm thấy, nhận tham số là mã số loại
    void findBook_addCart();            // Thêm vào giỏ hàng
    void findBook_rent();               // Lấy thông từ giỏ hàng -> thay đổi trạng thái -> lưu
    void findBook_cart();               // Lựa chọn đối với giỏ hàng
    void findBook_clear();              // Xóa giỏ hàng, xóa hàng nhập...

    void rentHistory();             // Khởi động chức năng: Đoc từ file -> điền vào bảng lịch sử

    void readNotif_beg();           // Xem thông báo chung ( tất cả )
    void readNotif_i(long i);       // Chi tiết 1 thông bá, nhận vào mã số thông báo

    void logout();                  // Đăng xuất
    void info_save();

private:
    QString QDateToString(const QDate&);
    QDate stringToQDate(QString);
    Ui::Reader *ui;
};

#endif // READER_H
