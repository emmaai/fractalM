#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T14:03:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = 3dhomopengl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow3d.cpp \
	functionglwidget.cpp \
	functioncube.cpp \
	imageglwidget.cpp \
	qtlogo.cpp \
	data_socket.cpp \
	netsettingdialog.cpp

HEADERS  += mainwindow3d.h \
	    functionglwidget.h \
	    functioncube.h \
	    imageglwidget.h \
	    qtlogo.h \
	    data_socket.h \
	    netsettingdialog.h

FORMS    += mainwindow3d.ui \
	    netsettingdialog.ui

QMAKE_CXXFLAGS += -pthread
#QMAKE_CXXFLAGS_WARN_ON -= -Wall

RESOURCES += \
    3dhomeo.qrc
