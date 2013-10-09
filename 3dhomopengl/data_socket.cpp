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
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(socketReady()));

}

rwSockData::~rwSockData()
{
    delete tcpSocket;
}

void rwSockData::connectToHost(hostAddress *host)
{
    qDebug() << "connect to host, thread" << this->thread();
    if(tcpSocket->state()==QAbstractSocket::ConnectingState || 
	    tcpSocket->state() == QAbstractSocket::ConnectedState)
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

void rwSockData::writeImg(char *imageBuffer)
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
    int paramSize = 1*sizeof(activeFunc); 
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
    char *tailPtr;
    char *headPtr;
    qint64 readSize=0;
    qint64 remainSize = 0;
    remainSize = tcpSocket->bytesAvailable();
    qDebug() << "available data size is" << remainSize;
    while(remainSize)
    {
	readSize = tcpSocket->read(readBuffer, 8*32768);
	headPtr= (char *)memmem(readBuffer, readSize, "<DATA", 5);
	tailPtr= (char *)memmem(readBuffer, readSize, "<\\DATA", 6);
	if(!headPtr && !tailPtr)	
	{
	    memcpy((char *)imagePtr, readBuffer, readSize); 
	    imagePtr += readSize;
	}else
	{
	    if(tailPtr > headPtr)	
	    {
		if(headPtr)
		    memcpy((char *)imagePtr, headPtr+5, tailPtr - headPtr -5); 
		else
		    memcpy((char *)imagePtr, readBuffer, tailPtr-readBuffer); 

		imagePtr = (unsigned long)imageBuffer;
		emit imageReady((char *)imageBuffer);    
	    }else
	    {
		if(tailPtr) 
		{
		    memcpy((char *)imagePtr, readBuffer, tailPtr-readBuffer); 
		    imagePtr = (unsigned long)imageBuffer;
		    emit imageReady((char *)imageBuffer); 
		    memcpy((char *)imagePtr, headPtr+5, readSize-(headPtr+5-readBuffer));
		    imagePtr += readSize-(headPtr+5-readBuffer);
		}else
		{
		    memcpy((char *)imagePtr, headPtr+5, readSize-(headPtr+5-readBuffer));
		    imagePtr += readSize-(headPtr+5-readBuffer);

		}
	    
	    }
	
	}
	
	remainSize -= readSize;

    }//while
}

void rwSockData::socketReady()
{
    emit connectedToHost();
}
