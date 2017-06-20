#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T12:37:14
#
#-------------------------------------------------

QT       += core gui\

	greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
	QMAKE_CXX.COMPILER_MACROS += g++4.6

TARGET = Assignment2_Test3
TEMPLATE = app
win32:RC_ICONS += icon.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    User.cpp \
    Account.cpp \
    RentBook.cpp \
    UserManager.cpp \
    Reader.cpp \
    Librarian.cpp \
    StartProgram.cpp \
    Notification.cpp \
    BookType.cpp \
    Book.cpp

HEADERS  += \
    User.h \
    Account.h \
    RentBook.h \
    UserManager.h \
    Reader.h \
    Librarian.h \
    StartProgram.h \
    Notification.h \
    BookType.h \
    Book.h

FORMS    += \
    UserManager.ui \
    Reader.ui \
    Librarian.ui \
    StartProgram.ui

RESOURCES += \
    resource.qrc


R_FIND = 1, R_FIND_OPT = 2, R_RENT_HIS = 3, R_INFO = 4, R_FIND_CART = 5, R_FIND_DONE = 6, R_ABOUT = 7, R_NOTIF = 8, R_NOTIF_OPT = 9
BTID = 0 , B_TITLE = 1, B_AUTHOR = 2, B_ID = 3, B_STATE = 4, B_ACCID = 5, B_NAME_RENT= 6 , ADD_DATE = 7
LIBID = 0, ACCID = 1, USN = 2, PW = 3, READER = 4, LIBRARIAN = 5, USM = 6
