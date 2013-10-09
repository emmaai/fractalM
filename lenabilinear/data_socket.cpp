#include "data_socket.h"
#include <QMutexLocker>
#include <QMessageBox>

rwSockData::rwSockData(QObject *parent):QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    imagePtr = (unsigned long)imageBuffer;
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServer()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromHost()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(sendSockError(QAbstractSocket::SocketError)));

}

rwSockData::~rwSockData()
{
    delete tcpSocket;
}

void rwSockData::connectToHost(hostAddress *host)
{
    qDebug() << "connect to host, thread" << this->thread();
    if(tcpSocket->isValid())
	return;
    tcpSocket->connectToHost(host->hostname, host->portid);    
}

void rwSockData::disconnectFromHost()
{
    qDebug() << "disconnect by host";
    tcpSocket->close();
}

void rwSockData::sendSockError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;
    errorString = tcpSocket->errorString();
    tcpSocket->close();
    emit rwSockError(&errorString);
}

void rwSockData::readSocket()
{
	qDebug() << "read the socket here"; 
}

void rwSockData::writeImg(unsigned char *imageBuffer)
{
    qDebug()<< "write the image data ";
    qint64 writeSize = 0;
    int imageSize =  *(int*)imageBuffer;
    QMutex mutex;
    qDebug() << "image size is" << imageSize;
    mutex.lock();
    writeSize = tcpSocket->write("<DATA");
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    writeSize=tcpSocket->write((char *)imageBuffer+sizeof(int), imageSize);
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    writeSize = tcpSocket->write("<\\DATA");
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    tcpSocket->waitForBytesWritten();
    mutex.unlock();
}

void rwSockData::writeParam(char *param)
{
    qDebug() << "write the param";
    int paramSize = 10*sizeof(activeFunc); 
    qint64 writeSize;
    QMutex mutex;
    writeSize = tcpSocket->write("<PARA");
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    writeSize=tcpSocket->write((char *)param, paramSize);
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    writeSize = tcpSocket->write("<\\PARA");
    if(writeSize < 0)
    {
	qDebug() << "Thread: write error"; 
    }
    tcpSocket->waitForBytesWritten();
    mutex.unlock();
}

void rwSockData::readServer()
{
    char readBuffer[8*32768];
    char *ptr;
    qint64 readSize=0;
    qint64 remainSize = 0;
    qDebug() << "available data size is" << tcpSocket->bytesAvailable();
    remainSize = tcpSocket->bytesAvailable();
    while(remainSize)
    {
	readSize = tcpSocket->read(readBuffer, 8*32768);
	if(ptr= (char *)memmem(readBuffer, readSize, "<DATA", 5))
	{
	    qDebug()<< "get the head" << (unsigned long)ptr;
	    memcpy((char *)imagePtr, ptr+5, readSize-(ptr+5-readBuffer)); 
	    imagePtr += readSize-(ptr+5-readBuffer);
	    return;
	}else if(ptr=(char *)memmem(readBuffer, readSize, "<\\DATA", 6))
	{
	    qDebug()<< "get the tail" << ptr;
	    memcpy((char *)imagePtr, readBuffer, ptr-readBuffer); 
	    imagePtr = (unsigned long)imageBuffer;
	    emit imageReady((unsigned char *)imageBuffer);    
	    return;
	}
	memcpy((char *)imagePtr, readBuffer, readSize); 
	imagePtr += readSize;
	remainSize -= readSize;
    }
}
