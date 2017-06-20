 #ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <QMainWindow>
#include "User.h"
#include "StartProgram.h"

namespace Ui {
class Librarian;
}

class Librarian : public QMainWindow, public User       // Kế thừa từ class User, Giao diện kết thừa từ QMainWindow
{
    Q_OBJECT

public:
    explicit Librarian(const User& = {}, QWidget *parent = 0);
    ~Librarian();
    void setInfo(long);         // Gán thông tin người dùng lúc đăng nhập vào chương trình
private slots:
    // Nhóm hàm khi thêm loại sách
    void addBook_verify();      // Xác thực thông tin khi thêm sách, hàm này được gọi khi người dùng đang nhập dữ liệu
    void addBook_clear();       // Xóa thông tin cũ trên dòng sau khi đã thêm sách, ẩn form , ẩn thông báo...
    void addBook_save();        // Lưu thông tin sách sau khi nhận được tín hiệu từ nút thêm sách ( đã qua xác thực)
    void addBook_connect();     // Kết nối tín hiệu cần thiết cho chức năng thêm sách ( dòng ghi dữ liệu, nút )
    // Thêm 1 cuốn sách vào loại sách có sẵn
    void add1Book_find();       // Hiển thị sách muốn thêm ( hiển thị thông báo không tin tìm thấy hoặc hiển thị form thông tin sách nếu tìm thấy)
    void add1Book_save();       // Lưu sách khi nhận được tín hiệu thêm (từ nút bấm)
    void add1Book_verify();     // Xác thực thông tin nhập vào
    // Tìm kiếm sách, liên kết với chức năng sửa sách,xóa sách
    void findBook_find();       // Tìm kiếm sách
    void findBook_connect();    // Kết nối tín hiệu cần thiết của tính năng này ( QPushButton, LineEdit,...)
    void findBook_clear();      // Xóa thông tin, ẩn bảng dữ liệu nếu không tìm thấy, ẩn thông báo
    // Tra cứu thông tin cuốn sách từ mã cuốn sách
    void searchBID();           //
    void searchBID_verify();
    // Giải quyết yêu cầu mượn sách
    void request_beg();         // Khởi tạo cdiệnhức năng: đọc file tìm thông tin điền vào bảng, nếu không thấy -> hiện thông báo...
    void request_clear();       // Xóa bảng thông tin, ẩn thông báo...
    void request_opt(int);      // Đọc chi tiết bản ghi, có thể xác thực từ đây, tham số là số thứ tự trên bảng liệt kê yêu cầu
    void request_cancel_i(int); // Từ chối yêu cầu, tham số là số thứ tự trên bảng liệt kê
    void request_save(int);     // Lưu thông tin mỗi lần từ chối, chấp nhận xuông file, sửa thông tin trong sách,người dùng, tham số là số thứ tự trên bảng liệt kê...
    void request_connect();     // Két nối tín hiệu cần thiét
    // Thay đổi thông tin sách
    void editBook_beg(long i);  // Sửa thông tin sách : điền thông tin cũ vào bảng,...
    void editBook_save();       // Lưu thông tin ( Kết nối với nút lưu)
    void editBook_list();
    // Giải quyết mất sách
    void lostBook_find();       // Đọc thông tin từ ô tìm kiếm, điền thông tin chi tiết vào bảng nếu tìm thấy, ẩn bảng - hiện thông báo nếu không tìm thấy
    void lostBook_clear();      // Xóa thông tin trong bảng, ẩn thông báo, ẩn bảng thông tin
    void lostBook_save();       // Lưu thông tin, tạo thông báo đến người dùng
    // Gửi thông báo
    void sendNotif_save();      // Lưu thông báo
    void sendNotif_clear();     // Xóa thông tin cũ (sau khi đã gửi xong)
    // Ghi nhận trả sách
    void receiveBook_clear();   // Ẩn form , ẩn label, xóa thông tin cũ
    void receiveBook_find();    // Tìm kiếm thông tin từ dữ liệu nhập vào, tương tác vớingười dùng tùy trường hợp (tìm thấy/ không timf thấy)
    void receiveBook_save();    //  Lưu lại thông tin
    // Đổi mật khẩu
    void info_save();
    void deleteBook(long);       // Xóa 1 cuốn sách
    void deleteBookType(long);  // Xóa 1 loại sách

    void deleteBookType_connect();



    void logout();              // Đăng xuất chương trình
private:
    Ui::Librarian *ui;          // Giao diện
};

#endif // LIBRARIAN_H
