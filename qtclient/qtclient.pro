#-------------------------------------------------
#
# Project created by QtCreator 2013-07-10T10:32:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data_socket.cpp \
    netsettingdialog.cpp \
    colorlabel.cpp \
    renderframe.cpp \
    functionrect.cpp

HEADERS  += mainwindow.h \
    data_socket.h \
    netsettingdialog.h \
    colorlabel.h \
    renderframe.h \
    functionrect.h

FORMS    += mainwindow.ui \
    netsettingdialog.ui

QMAKE_CXXFLAGS += -pthread
#QMAKE_CXXFLAGS_WARN_ON -= -Wall

RESOURCES += \
    qtclient.qrc
