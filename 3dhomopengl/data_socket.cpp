#include "data_socket.h"
#include <QMutexLocker>
#include <QMessageBox>

rwSockData::rwSockData(QObject *parent):QObject(parent), tcpServer(0),networkSession(0), tcpSocket(0)
{
    imagePtr = (unsigned long)imageBuffer;

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) 
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    } else 
    {
        sessionOpened();
    }

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
    qDebug() << "socket is ready";
    emit connectedToHost();
}

void rwSockData::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen (QHostAddress::Any, 50000)) {
        tcpServer->close();
        return;
    }

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(connectToClient()));
}

void rwSockData::connectToClient()
{
    qDebug() << "incoming connection";
    tcpSocket = tcpServer->nextPendingConnection();
    qDebug() << "tcpSocket is" << tcpSocket;
    socketReady();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServer()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(sendSockError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()), tcpSocket, SLOT(deleteLater()));

}
