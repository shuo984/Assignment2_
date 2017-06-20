
#include "BookType.h"
BookType::BookType(long bid, std::string name, std::string author, std::string typ, std::string summ, int y,
                   long times, long free, long av, long amou)
    :bookID(bid), year(y), isFree(free), available(av), amount(amou), timesAccess(times)
{
    setTitle(name);
    setAuthor(author);
    setTimesAcess(times);
    setType(typ);
    setSummary(summ);
    setAmount(amount);
}
void BookType::setAuthor(std::string author)
{
    int size = (author.size() < B_AUTHOR_SIZE ? author.size() : B_AUTHOR_SIZE - 1);
    author.copy(bookAuthor, size);
    bookAuthor[size] = '\0';
}
void BookType::setBookID(long id)
{
    bookID = id;
}
void BookType::setTimesAcess(long times)
{
    timesAccess = times;
}
void BookType::setTitle(std::string name)
{
    int size = (name.size() < B_TITLE_SIZE ? name.size() : B_TITLE_SIZE - 1);
    name.copy(bookTitle, size);
    bookTitle[size] = '\0';
}
std::string BookType::getAuthor() const
{
    return bookAuthor;
}
std::string BookType::getName() const
{
    return bookTitle;
}
long BookType::getTimeAccess() const
{
    return timesAccess;
}
long BookType::getBookID() const
{
    return bookID;
}
int BookType::getYear() const
{
    return year;
}
void BookType::setType(std::string typ)
{
    int size = typ.size() < B_TYPE_SIZE ? typ.size() : B_TYPE_SIZE - 1;
    typ.copy(type, size);
    type[size] = '\0';
}
std::string BookType::getType() const
{
    return type;
}
void BookType::setSummary(std::string s)
{
    int size = s.size() < B_SUM_SIZE ? s.size() : B_SUM_SIZE - 1;
    s.copy(summary, size);
    summary[size] = '\0';
}


void BookType::setAmount(int amou)
{
    amount = amou;
}
int BookType::getAmount() const
{
    return amount;
}
void BookType::readData(long bid)
{
    std::ifstream bookFin("book_data.txt");
    if (!bookFin)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFin.seekg((bid - 1) * sizeof(BookType));
    bookFin.read(reinterpret_cast<char*>(this), sizeof(BookType));
    bookFin.close();
}
void BookType::saveData()
{
    std::fstream bookFout("book_data.txt");
    if (!bookFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFout.seekp((getBookID() - 1) * sizeof(BookType));
    bookFout.write(reinterpret_cast<char*>(this), sizeof(BookType));
    bookFout.close();
}
void BookType::saveData(long id)
{
    std::fstream bookFout("book_data.txt");
    if (!bookFout)
    {
        QMessageBox message;
        message.setWindowTitle("Lỗi chương trình");
        message.setText("Không thể đọc file");
        message.exec();
    }
    bookFout.seekp((id - 1) * sizeof(BookType));
    bookFout.write(reinterpret_cast<char*>(this), sizeof(BookType));
    bookFout.close();
}
void BookType::setYear(int y)
{
    year = y;
}
std::string BookType::getSummary() const
{
    return summary;
}
void BookType::setAvailable(long av)
{
    available = av;
}

long BookType::getAvailable() const
{
    return available;
}
void BookType::setNFree(long num)
{
    isFree = num;
}

long BookType::getNFree() const
{
    return isFree;
}
