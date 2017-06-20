#include "Book.h"



Book::Book(long tID, long bid, QDate addD, int st , long acc)
    :typeID(tID), bookID(bid), addDate(addD), state(st), rentID(acc)
{}
long Book::getTypeBook() const
{
    return typeID;
}
void Book::setTypeBook(long id)
{
    typeID = id;
}

long Book::getBookID() const
{
    return bookID;
}
void Book::setBookID(long id)
{
    bookID = id;
}

void Book::setState(int st)
{
    state = st;
}

long Book::getState() const
{
    return state;
}
void Book::readData(long id)
{
    std::ifstream bookFin("book_data_list.txt");
    if (!bookFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFin.seekg((id - 1) * sizeof(Book));
    bookFin.read(reinterpret_cast<char*>(this), sizeof(Book));
    bookFin.close();
}

void Book::saveData(long id)
{
    std::fstream bookFout("book_data_list.txt");
    if (!bookFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFout.seekp((id - 1) * sizeof(Book));
    bookFout.write(reinterpret_cast<char*>(this), sizeof(Book));
    bookFout.close();
}
void Book::saveData()
{
    std::fstream bookFout("book_data_list.txt");
    if (!bookFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFout.seekp((getBookID() - 1) * sizeof(Book));
    bookFout.write(reinterpret_cast<char*>(this), sizeof(Book));
    bookFout.close();
}
void Book::setAddDate(const QDate& date)
{
    addDate = date;
}

QDate Book::getAddDate() const
{
    return addDate;
}
long Book::getRentID() const
{
    return rentID;
}
void Book::setRentID(long id)
{
    rentID = id;
}
