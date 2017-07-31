#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T12:01:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OperateWithSN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readstationtbl.cpp \
    writestationtbl.cpp

HEADERS  += mainwindow.h \
    readstationtbl.h \
    writestationtbl.h

FORMS    += mainwindow.ui \
    writestationtbl.ui

INCLUDEPATH += ./ \
