//
// Created by hvlpro98 on 02/05/2017.
//

#ifndef ASSIGNMENT2_BOOK_H
#define ASSIGNMENT2_BOOK_H

#include <iostream>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QDate>
const int B_TYPE_SIZE = 50;
const int B_AUTHOR_SIZE = 100;
const int B_TITLE_SIZE = 100;
const int B_SUM_SIZE = 400;

class BookType
{
public:
    BookType(long = 0, std::string tit = "", std::string author = "", std::string typ = "", std::string summ = "", int y = 0,
             long times= 0, long free = 0, long av = 0, long amou  = 0);
    std::string getName() const;	// Trả về tên sách
    std::string getAuthor() const;	// Trả về tác giả
    long getTimeAccess() const;		// Trả về lượt xem sách đó
    long getBookID() const;			// Trả về mã số loại sách
    void setTitle(std::string);		// Gán tên sách
    void setAuthor(std::string);	// Gán tên tác giả
    void setBookID(long);			// Gán mã số sách
    void setTimesAcess(long);		// Gán số lượt truy cập
    int getYear() const;			// Trả về năm xuất bản
    std::string getType() const;	// Trả về thể loại sách

    int getAmount() const;			// Trả về số lượng tổng cộng       ( có sẵn + cho mượn)
    std::string getSummary() const; // Trả về tóm tắt
    long getAvailable() const;      // Trả về số sách sẵn có trong kho ( chưa được đặt + đã được đặt)

    void readData(long);			// Đọc thông tin từ file, tham số đầu vào là mã số
    void saveData();				// Lưu dữ liệu vào file theo mã số hiện tại
    void saveData(long);            // Lưu thông tin theo vị trí định trước
    void setYear(int);              // Gán năm xuất bản
    void setAvailable(long);        // Gán số lượng hiện có
    void setType(std::string);		// áchGán thể loại
    void setSummary(std::string);	// Gán tóm tắt
    void setAmount(int);			// Gán số lượng

    void setNFree(long);            // Lấy số lượng chưa được đặt trước
    long getNFree() const;          // Lấy số lượng chưa được đặt trước
private:
    long bookID;					// Mã loại sách
    char bookTitle[B_TITLE_SIZE];   // Tên sách
    char bookAuthor[B_AUTHOR_SIZE];	// Tác giả
    char type[B_TYPE_SIZE];			// Thể loại
    char summary[B_SUM_SIZE];			// Tóm tắt
    int year;						// Năm xuất bản
    long isFree;                    // Số sách chưa được đặt, có thể được cho mượn
    long available;                 // Số lượn sẵn có
    long amount;					// Số luượng tổng cộng
    long timesAccess;				// Số lần truy cập

};
#endif //ASSIGNMENT2_BOOK_H
