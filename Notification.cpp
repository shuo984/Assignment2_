#include "Notification.h"

Notification::Notification(long i, long nid, std::string tit, std::string no, QDate date, bool st)
    :id(i), accID(nid), dateSent(date), state(st)
{
    setNotif(no);
    setTitle(tit);
}

void Notification::setNotif(std::string str)
{
    int size = (str.size()<NOTIF_SIZE?str.size():NOTIF_SIZE -1);
    str.copy(notif,size);
    notif[size] = '\0';
}

std::string Notification::getNotif() const
{
    return notif;
}
void Notification::setAccID(long id)
{
    accID = id;
}

long Notification::getAccID() const
{
    return accID;
}
void Notification::setState(bool st)
{
    state = st;
}

bool Notification::getState() const
{
    return state;
}
void Notification::setTitle(std::string tit)
{
    int size = tit.size()<TITLE_SIZE ? tit.size() : TITLE_SIZE - 1;
    tit.copy(title,size);
    title[size] = '\0';
}
void Notification::readData(long i)
{
    std::ifstream notifFin("notif_data.txt");
    notifFin.seekg((i - 1) * sizeof(Notification));
    notifFin.read(reinterpret_cast<char*>(this), sizeof(Notification));
    notifFin.close();
}

void Notification::saveData()
{
    std::fstream notifFout("notif_data.txt");
    notifFout.seekp((id - 1) * sizeof(Notification));
    notifFout.write(reinterpret_cast<char*>(this), sizeof(Notification));
    notifFout.close();
}
void Notification::saveData(long i)
{
    std::fstream notifFout("notif_data.txt");
    notifFout.seekp((i - 1) * sizeof(Notification));
    notifFout.write(reinterpret_cast<char*>(this), sizeof(Notification));
    notifFout.close();
}

std::string Notification::getTitle() const
{
    return title;
}
void Notification::setDateSent(QDate date)
{
    dateSent = date;
}

QDate Notification::getDateSent() const
{
    return dateSent;
}
void Notification::setID(long i)
{
    id = i;
}
long Notification::getID() const
{
    return id;
}
