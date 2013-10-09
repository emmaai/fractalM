#ifndef MAINWINDOW3D_H
#define MAINWINDOW3D_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "data_socket.h"
#include "typedef.h"


namespace Ui {
class MainWindow3D;
}

class MainWindow3D : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow3D(QWidget *parent = 0);
    ~MainWindow3D();
    hostAddress host;
    unsigned char *imageBuffer;
    unsigned long paramBuffer;
public slots:
    void open();
    void netsetting();
    void displayError(QString *);
    void connectToHost();
    void disconnectFromHost();

signals:
    void invokeConnect(hostAddress *);
    void invokeDisconnect();
    void writeData(unsigned char *);


    
private:
    Ui::MainWindow3D *ui;

    void creatActions();
    void loadFile(const QString );
    QString hostname;
    quint16 portid;
    rwSockData	*rwSocket;
    QThread *rwThread;


};

#endif // MAINWINDOW3D_H
