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
    viewer.cpp

HEADERS  += mainwindow3d.h \
	    functionglwidget.h \
	    functioncube.h \
	    imageglwidget.h \
	    qtlogo.h \
	    data_socket.h \
	    netsettingdialog.h \
    viewer.h

FORMS    += mainwindow3d.ui \
	    netsettingdialog.ui

DEFINES += EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS TGT_HAS_DEVIL TGT_WITHOUT_DEFINES TIXML_USE_STL \
        UNIX VRN_MODULE_ADVANCEDLIGHTING VRN_MODULE_BASE VRN_MODULE_CONNEXE \
        VRN_MODULE_CORE VRN_MODULE_DEVIL VRN_MODULE_DYNAMICGLSL VRN_MODULE_FLOWREEN \
        VRN_MODULE_PLOTTING VRN_MODULE_PVM VRN_MODULE_RANDOMWALKER \
        VRN_MODULE_SEGY VRN_MODULE_STAGING VRN_MODULE_STEREOSCOPY VRN_MODULE_VOLUMELABELING \
        VRN_MODULE_ZIP __STDC_CONSTANT_MACROS

QMAKE_CXXFLAGS += -g -pthread -fpermissive
#QMAKE_LFLAGS += -rdynamic

#QMAKE_CXXFLAGS_WARN_ON -= -Wall
INCLUDEPATH += C:\Qt\voreen-src-4.4-win \
            C:\Qt\voreen-src-4.4-win\include \
            C:\Qt\voreen-src-4.4-win\ext \
            C:\Qt\voreen-src-4.4-win\modules \
            C:\Qt\boost_1_55_0 \
            C:\Qt\glew-1.10.0\include \
            C:\sharefolder\libQGLViewer-2.4.0


LIBS += -LC:\Qt\voreen-src-4.4-win\bin \
        -LC:\Qt\glew-1.10.0\lib \
        -LC:\Qt\boost_1_55_0\stage\lib \
        -LC:\sharefolder\build-libQGLViewer-2.4.0-Desktop-Release\QGLViewer\release \
        -LC:\Qt\voreen-src-4.4-win\modules\devil\ext\il\lib\win64 \
        -lQGLViewer2 \
        -lvoreen_qt \
        -lvoreen_core \
        -ltgt \
        -lglew32 \
        -lboost_program_options-mgw48-mt-1_55 \
        -lboost_system-mgw48-mt-1_55 \
        -lboost_thread-mgw48-mt-1_55 \
        -ldevil -lilu \
        -lglu32 \
        -lopengl32 \
        -lpsapi \
        -lversion

RESOURCES += \
    3dhomeo.qrc
