#include "StartProgram.h"
#include <QApplication>
#include <QDateTime>
#include <QDate>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    StartProgram c;
    c.show();




    return a.exec();
}
