#ifndef DATA_SOCKET_H
#define DATA_SOCKET_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <QObject>
#include <QtCore>
#include "typedef.h"


class rwSockData:public QObject
{
    Q_OBJECT
    QString errorString;

public:
    rwSockData(QObject *parent=0);
    ~rwSockData();
public slots:
    void connectToHost(hostAddress *);
    void disconnectFromHost();
    void sendSockError(QAbstractSocket::SocketError);
    void readSocket();
    void writeImg(unsigned char *);
    void writeParam(char *);
    void readServer();
signals:
    void rwSockError(QString *);
    void finished();
    void imageReady(unsigned char *);

private:
    QTcpSocket *tcpSocket;
    unsigned char imageBuffer[3*1024*1024];
    unsigned long imagePtr;
};

#endif // DATA_SOCKET_H
