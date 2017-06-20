#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QDate>
#include <string>
#include <fstream>
#include <iostream>

const int NOTIF_SIZE = 500;
const int TITLE_SIZE = 100;

class Notification
{
public:
    Notification(long id = 0, long aid = 0 , std::string tit = "", std::string note = "", QDate sentD = {} , bool st = false);
    void setNotif(std::string);                 // Gán nội dung
    std::string getNotif() const;               // Trả về nội dung
    void setAccID(long);                        // Gán mã số tài khoản
    long getAccID() const;                      // Trả về mã số tài khoản ( ứng với thông báo đó )
    void setState(bool);                        // Gán trạng thái ( Đã xem - Chưa xem )
    bool getState() const;                      // Trả về trạng thái
    void setTitle(std::string);                 // Gán tiêu dề thông báo
    std::string getTitle() const;               // Trả về tiêu dề thông báo
    void setDateSent(QDate);                    // Gán ngày gửi
    QDate getDateSent() const;                  // Trả về ngày gửi
    void setID(long);                           // Gán mã số thông báo
    long getID() const;                         // Trả về mã số thông báo

    void readData(long);                        // Đọc thông báo từ file
    void saveData();                            // Lưu thông báo xuống file
    void saveData(long );                       // Lưu thông báo xuông file
private:
    long id;                                    // Mã số
    long accID;                                 // Mã số tài khoản nhận
    char title[TITLE_SIZE];                     // Tiêu đề
    char notif[NOTIF_SIZE];                     // Nội dung thông báo
    QDate dateSent;                             // Ngày gửi
    bool state;                                 // Trạng thái
};

    #endif // NOTIFICATION_H
