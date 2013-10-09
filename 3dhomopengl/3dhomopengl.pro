#-------------------------------------------------
#
# Project created by QtCreator 2013-08-13T14:03:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl xml

TARGET = 3dhomopengl
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow3d.cpp \
	functionglwidget.cpp \
	functioncube.cpp \
	imageglwidget.cpp \
	qtlogo.cpp \
	data_socket.cpp \
	netsettingdialog.cpp \
    viewer.cpp \
    clipplane.cpp

HEADERS  += mainwindow3d.h \
	    functionglwidget.h \
	    functioncube.h \
	    imageglwidget.h \
	    qtlogo.h \
	    data_socket.h \
	    netsettingdialog.h \
    viewer.h \
    clipplane.h

FORMS    += mainwindow3d.ui \
	    netsettingdialog.ui

DEFINES += EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS TGT_HAS_DEVIL TGT_WITHOUT_DEFINES TIXML_USE_STL \
        UNIX VRN_MODULE_ADVANCEDLIGHTING VRN_MODULE_BASE VRN_MODULE_CONNEXE \
        VRN_MODULE_CORE VRN_MODULE_DEVIL VRN_MODULE_DYNAMICGLSL VRN_MODULE_FLOWREEN \
        VRN_MODULE_OPENCL VRN_MODULE_PLOTTING VRN_MODULE_PVM VRN_MODULE_RANDOMWALKER \
        VRN_MODULE_SEGY VRN_MODULE_STAGING VRN_MODULE_STEREOSCOPY VRN_MODULE_VOLUMELABELING \
        VRN_MODULE_ZIP VRN_SHARED_LIBS __STDC_CONSTANT_MACROS

QMAKE_CXXFLAGS += -pthread -fPIC
QMAKE_LFLAGS += -rdynamic

#QMAKE_CXXFLAGS_WARN_ON -= -Wall
INCLUDEPATH += /home/emma/Downloads/voreen-src-4.3-unix/include \
            /home/emma/Downloads/voreen-src-4.3-unix/ext \
            /home/emma/Downloads/voreen-src-4.3-unix/modules

LIBS += -L/home/emma/Downloads/voreen-src-4.3-unix/bin \
        -lQGLViewer \
        -ltgt \
        -lvoreen_core \
        -lvoreen_qt \
        -lGLU \
        -lGL \
        -lGLEW \
        -lOpenCL

RESOURCES += \
    3dhomeo.qrc
