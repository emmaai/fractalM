/********************************************************************************
** Form generated from reading UI file 'mainwindow3d.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW3D_H
#define UI_MAINWINDOW3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QGLViewer/qglviewer.h"
#include "viewer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow3D
{
public:
    QAction *actionOpen;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionNetwork;
    QAction *actionHR;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QSplitter *splitter;
    Viewer *viewerFuncO;
    QSplitter *splitter_2;
    Viewer *viewerFunc;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Connection;
    QMenu *menu_Settings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow3D)
    {
        if (MainWindow3D->objectName().isEmpty())
            MainWindow3D->setObjectName(QStringLiteral("MainWindow3D"));
        MainWindow3D->resize(998, 757);
        actionOpen = new QAction(MainWindow3D);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/resource/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionConnect = new QAction(MainWindow3D);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/resource/Network_Globe_Connected_Icon_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon1);
        actionDisconnect = new QAction(MainWindow3D);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/resource/Network_Globe_Disconnected_Icon_256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon2);
        actionNetwork = new QAction(MainWindow3D);
        actionNetwork->setObjectName(QStringLiteral("actionNetwork"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/resource/Network Connection Internet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetwork->setIcon(icon3);
        actionHR = new QAction(MainWindow3D);
        actionHR->setObjectName(QStringLiteral("actionHR"));
        centralWidget = new QWidget(MainWindow3D);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        viewerFuncO = new Viewer(splitter);
        viewerFuncO->setObjectName(QStringLiteral("viewerFuncO"));
        splitter->addWidget(viewerFuncO);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        viewerFunc = new Viewer(splitter_2);
        viewerFunc->setObjectName(QStringLiteral("viewerFunc"));
        splitter_2->addWidget(viewerFunc);
        splitter_3->addWidget(splitter_2);

        gridLayout->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow3D->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow3D);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 998, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Connection = new QMenu(menuBar);
        menu_Connection->setObjectName(QStringLiteral("menu_Connection"));
        menu_Settings = new QMenu(menuBar);
        menu_Settings->setObjectName(QStringLiteral("menu_Settings"));
        MainWindow3D->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow3D);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow3D->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow3D);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow3D->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Connection->menuAction());
        menuBar->addAction(menu_Settings->menuAction());
        menu_File->addAction(actionOpen);
        menu_Connection->addAction(actionConnect);
        menu_Connection->addAction(actionDisconnect);
        menu_Settings->addAction(actionNetwork);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionNetwork);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHR);

        retranslateUi(MainWindow3D);

        QMetaObject::connectSlotsByName(MainWindow3D);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow3D)
    {
        MainWindow3D->setWindowTitle(QApplication::translate("MainWindow3D", "MainWindow3D", 0));
        actionOpen->setText(QApplication::translate("MainWindow3D", "&Open", 0));
        actionConnect->setText(QApplication::translate("MainWindow3D", "&Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow3D", "&Disconnect", 0));
        actionNetwork->setText(QApplication::translate("MainWindow3D", "&Network", 0));
        actionHR->setText(QApplication::translate("MainWindow3D", "High Resolution", 0));
#ifndef QT_NO_TOOLTIP
        actionHR->setToolTip(QApplication::translate("MainWindow3D", "<html><head/><body><p>Generate the high resolution volume</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        menu_File->setTitle(QApplication::translate("MainWindow3D", "&File", 0));
        menu_Connection->setTitle(QApplication::translate("MainWindow3D", "&Connection", 0));
        menu_Settings->setTitle(QApplication::translate("MainWindow3D", "&Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow3D: public Ui_MainWindow3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW3D_H
