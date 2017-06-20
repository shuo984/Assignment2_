#ifndef ASSIGNMENT2_RENTBOOK_H
#define ASSIGNMENT2_RENTBOOK_H

#include "Date.h"
#include <fstream>
#include <string>
#include <QDate>
enum {RENT_NORMAL  = 1, WAIT_RENT = 2, RENT_LATE =3, RENT_BACKUP =4, RENT_FAIL = 5, RENT_LOST = 6};
class RentBook
{
public:
    RentBook(long rid = 0, long aid = 0, QDate = {}, QDate = {}, QDate = {}, long bid = 0, long btid = 0, int st = RENT_NORMAL, long = 0);
    void setRentID(long);                       // Gán mã số mượn
    void setAccID(long);                        // Gán tài khoản mượn
    void setRentDate(const QDate &);            // Gán ngày mượn
    void setExpireDate(const QDate &);          // Gán ngày trả
    void setBookID(long);                       // Gán mã số sách mượn
    void setFine(long);                         // Gán thông tin phạt
    void setReturnDate(QDate);                  // Gán ngày trả

    long getRentID() const;                     // Trả về mã số mượn
    long getAccID() const;                      // Trả về mã số tài khoản
    QDate getRentDate() const;                  // Trả về ngày mượn
    QDate getExpDate() const;                   // Trả về ngày hết hạn
    long getBookID() const;                     // Trả về mã số sách
    long getFine() const;                       // Trả về số tiền phạt
    QDate getReturnDate() const;                // Trả về ngày trả sách
    void saveData();                            // Lưu thông tin xuống file
    void saveData(long);                        // Lưu thông tin xuống file dựa vào tham số
    void readData(long);                        // Đọc thông tin từ file
    void setBookTypeID(long);                   // Gán mã số loại sách
    long getBookTypeID() const;                 // Trả về mã số loại sách

    int getState() const;                       // Trả về trạng thái
    void setState(int) ;                        // Gán trạng thái


private:
    long rentID;                                // Mã số bản ghi mượn
    long accID;                                 // Mã số tài khoản mượn
    QDate rentDate;                             // Ngày mượn
    QDate expDate;                              // Ngày hết hạn
    QDate returnDate;                           // Ngày trả
    long bookID;                                // Mã số sách
    long bookTypeID;                            // Mã số loại sách
    long fine;                                  // Tiền phạt
    int state;                                  // Trạng thái
};
#endif // !ASSIGNMENT2_RENTBOOK_H
