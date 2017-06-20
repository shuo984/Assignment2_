#ifndef ASSIGNMENT2_USER_H
#define ASSIGNMENT2_USER_H


#include "Account.h"
#include "BookType.h"
#include "Date.h"
#include "Book.h"
#include "RentBook.h"
#include "Notification.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


const size_t NAME_SIZE = 30;
const size_t DOB_SIZE = 11;
const size_t JOB_SIZE = 20;
const size_t MAIL_SIZE = 50;
const size_t NUM_ACCOUNT = 5;
const size_t MAX_RENT = 15;
class User
{
public:
    User(long lid = 0, long uid = 0, long pid =0 , std::string name = "", std::string dob = "", std::string job = "", std::string mail = "",
        long[NUM_ACCOUNT] = {}, int numA = 0, int st = 1);
    User(long lid, long uid, long pid, std::string name, std::string dob, std::string job, std::string mail, int st);
    void setLibID(long);                        // Gán mã số thư viện
    void setUserID(long);                       // Gán MSSV/MSGV
    void setPID(long);                          // Gán số CMND
    void setFullName(std::string);              // Gán tên
    void setDayOfB(std::string);                // Gán ngày tháng năm sinh
    void setJob(std::string);                   // Gán nghề nghiệp
    void setMailAddr(std::string);              // Gán địa chỉ email
    void setAccountList(long[NUM_ACCOUNT]);     // Gán danh sách tài khoản
    void setNumAccount(long);                   // Gán số lượng tài khoản đã đăng kí
    void setState(int);                         // Gán trạng thái
    long getLibID() const;                      // Trả về mã số thư viện
    long getUserID() const;                     // Trả về MSSV/MSGV
    long getUserPID() const;                    // Trả về số CMND
    std::string getFullName() const;            // Trả về tên đầy đủ
    std::string getDOB() const;                 // Trả về ngày tháng năm sinh
    std::string getMailAddr() const;            // Trả về địa chỉ email
    std::string getJob() const;                 // Trả về nghề nghiệp
    long* getAccountList() ;                    // trả về danh sách tài khoản
    long getNumAccount() const;                 // Trả về số lượng tài khoản
    int getState() const;                       // Trả về trạng thái
    void readUser(long);                        // Đọc thông tin từ file
    void saveUser();                            // Lưu thông tin người dùng xuống file
    void saveUser(long);                        // Lưu thông tin người dùng xuống file theo vị trí xác định trước

    void addMoreAccount(long);                  // Thêm tài khoản
    void deleteUser(int);                       // Xóa ngươi dùng

    static void setNBookType(long);             // Gán Số lượng loại sách
    static long getNBookType();                 // Trả về số loại sách
    static void setNBook(long);                 // Gán số sách
    static long getNBook();                     // Trả về số sách
    static void setNumUser(long);               // Gán số lượng người dùng
    static long getNumUser();                   // Trả về số lượng người dùng
    static void setFAccount(long);              // Gán số lượng tài khoản
    static long getFAccount();                  // Trả về số lượng tài khoản
    static void setFNumRent(long);              // Gán số bản ghi mượn sách
    static long getFNumRent();                  // Trả về số bản ghi mượn sách
    static void setNNotif(long);                // Gán số thông báo đã gửi
    static long getNNotif();                    // Trả về số thông báo đã gửi
    static void setParam(long , int );          // Gán tham số chương trình ( Hỗ trợ các hàm static trên )
    static long getParam(int);                  // Trả về tham số chương trình ( Hỗ trợ các hàm static trên )
    static bool Search(std::string, std::string); // Tìm kiếm
    QString QDateToString(const QDate& date);   // Chuyển dạng ngày tháng sang chuỗi
    QDate stringToQDate(QString date);          // Chuyển chuỗi sang ngày tháng


private:
    long libID;				// Ma so thu vien
    long userID;					// Ma so sinh vien / giao vien
    long PID;						// CMND
    char fullName[NAME_SIZE];		// Ten day du
    char dayOfBirth[DOB_SIZE];		// Ngay thang nam sinh
    char userJob[JOB_SIZE];			// Nghe nghiep
    char mailAddr[MAIL_SIZE];       // Dia chi emailáng
    int numAccount;                 // Số lượng tài khoản đã đăng kí
    long listAccount[NUM_ACCOUNT];	// Danh sach tai khoan
    int state;					// Trang thai hoat dong
};
#endif // !ASSIGNMENT2_USER_H
