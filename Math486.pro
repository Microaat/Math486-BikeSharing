#-------------------------------------------------
#
# Project created by QtCreator 2018-04-25T09:17:39
#
#-------------------------------------------------

QT       += core gui \
         widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Math486
TEMPLATE = app


SOURCES += main.cpp \
    Components/bikenetwork.cpp \
    Components/bikestation.cpp \
    Gui/roadwindow.cpp \
    Gui/mainwindow.cpp \
    Graphics/road.cpp

HEADERS  += mainwindow.h \
    Components/bikenetwork.h \
    Components/bikestation.h \
    Gui/roadwindow.h \
    Gui/mainwindow.h \
    Graphics/road.h

FORMS    += mainwindow.ui \
    roadwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
