#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T10:50:43
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
DESTDIR   =$$PWD
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtWuziqi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GameModel.cpp \
    easymusic.cpp

HEADERS  += mainwindow.h \
    GameModel.h \
    ../../I2P(II)_Qt_student/snoopy_1/easymusic.h \
    easymusic.h

RESOURCES += \
    resource.qrc

DISTFILES +=
