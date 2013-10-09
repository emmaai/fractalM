#include "mainwindow3d.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow3D w;
    w.show();
    
    return a.exec();
}
