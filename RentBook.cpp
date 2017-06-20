#include "RentBook.h"
using namespace std;
RentBook::RentBook(long rid, long aid, QDate rentD, QDate expireD, QDate returnD ,  long bid, long btid, int st, long f)
    :rentID(rid),
    accID(aid),
    rentDate(rentD),
    expDate(expireD),
    returnDate(returnD),
    bookID(bid),
    bookTypeID(btid),
    state(st),
    fine(f)
{}
void RentBook::setRentID(long rid)
{
    rentID = rid;
}
void RentBook::setAccID(long aid)
{
    accID = aid;
}
void RentBook::setRentDate(const QDate &rent)
{
    rentDate = rent;
}
void RentBook::setExpireDate(const QDate &exp)
{
    expDate = exp;
}
void RentBook::setBookID(long bid)
{
    bookID = bid;
}

long RentBook::getRentID() const
{
    return rentID;
}
long RentBook::getAccID() const
{
    return accID;
}
QDate RentBook::getRentDate() const
{
    return rentDate;
}
QDate RentBook::getExpDate() const
{
    return expDate;
}
long RentBook::getBookID() const
{
    return bookID;
}
void RentBook::saveData()
{
    fstream dataFout("rent_data.txt");
    dataFout.seekp((rentID - 1) * sizeof(RentBook));
    dataFout.write(reinterpret_cast<char*>(this), sizeof(RentBook));
    dataFout.close();
}
void RentBook::saveData(long rid)
{
    fstream dataFout("rent_data.txt");
    dataFout.seekp((rid - 1) * sizeof(RentBook));
    dataFout.write(reinterpret_cast<char*>(this), sizeof(RentBook));
    dataFout.close();
}
void RentBook::readData(long rid)
{
    fstream dataFin("rent_data.txt");
    dataFin.seekg((rid - 1) * sizeof(RentBook));
    dataFin.read(reinterpret_cast<char*>(this), sizeof(RentBook));
    dataFin.close();
}
int RentBook::getState() const
{
    return state;
}
void RentBook::setState(int st)
{
    state = st;
}
void RentBook::setFine(long f)
{
    fine = f;
}
long RentBook::getFine() const
{
    return fine;
}
void RentBook::setReturnDate(QDate d)
{
    returnDate = d;
}
QDate RentBook::getReturnDate() const
{
    return returnDate;
}
void RentBook::setBookTypeID(long id)
{
    bookTypeID = id;
}

long RentBook::getBookTypeID() const
{
    return bookTypeID;
}
