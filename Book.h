#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QDate>
enum {B_AVAIL = 0, B_RENT = 1, B_LOST = 2};     // Tình trạng sách : Có sẵn trong kho - Được mượn - Bị mất
class Book
{
public:
    Book(long tID = 0, long bid = 0, QDate ={}, int st = 0, long = 0);    //
    long getTypeBook() const;       // Trả về mã loại sách
    void setTypeBook(long);         // Gán mã thể loại
    long getBookID() const;         // Trả về mã số cuốn sách
    void setBookID(long);           // Gán mã cuốn sách
    void setState(int);             // Gán trạng thái
    long getState() const;          // Trả về trạng thái
    void setAddDate(const QDate&);  // Gán ngày thêm
    QDate getAddDate() const;       // Trả về ngày thêm
    long getRentID() const;
    void setRentID(long);

    void readData(long);            // Đọc thông tin từ file, tham số là mã số sách
    void saveData(long);            // Lưu thông tin xuông file theo mã số sách
    void saveData();                // Lưu thông tin xuông file



private:
    long typeID;                    // Mã loại sách
    long bookID;                    // Mã số sách
    QDate addDate;                  // Ngày thêm
    int state;                      // Trạng thái
    long rentID;                    // Mã mượn
};

#endif // BOOK_H
