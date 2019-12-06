#-------------------------------------------------
#
# Project created by QtCreator 2018-08-23T12:05:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTCube
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cube.cpp \
    setup.cpp

HEADERS  += mainwindow.h \
    cube.h \
    setup.h

FORMS    += mainwindow.ui \
    setup.ui

RESOURCES += \
    resourses.qrc
