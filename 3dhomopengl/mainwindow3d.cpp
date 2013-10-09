#include "mainwindow3d.h"
#include "ui_mainwindow3d.h"
#include "netsettingdialog.h"

MainWindow3D::MainWindow3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3D)
{
    ui->setupUi(this);
    
    creatActions();
    hostname = "localhost";
    portid = 50000;
    rwSocket = new rwSockData;
    rwThread = new QThread;
    rwSocket->moveToThread(rwThread);

    connect(ui->widgetL, SIGNAL(xRotationChanged(int)), ui->widgetImgL, SLOT(setXRotation(int)));
    connect(ui->widgetL, SIGNAL(yRotationChanged(int)), ui->widgetImgL, SLOT(setYRotation(int)));
    connect(ui->widgetL, SIGNAL(zRotationChanged(int)), ui->widgetImgL, SLOT(setZRotation(int)));

    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setXTParam(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setYTParam(int)));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setZTParam(int)));
    connect(ui->pSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setPParam(int)));

    connect(rwSocket, SIGNAL(rwSockError(QString *)), this, SLOT(displayError(QString *)));
    //connect(this, SIGNAL(invokeConnect(hostAddress *)), rwSocket, SLOT(connectToHost(hostAddress *)));
    //connect(this, SIGNAL(invokeDisconnect()), rwSocket, SLOT(disconnectFromHost()));
    connect(ui->widgetImgL, SIGNAL(writeImage(char *)), rwSocket, SLOT(writeImg(char *)));
    connect(ui->widgetImgL, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));
    connect(rwSocket, SIGNAL(imageReady(char *)), ui->widgetImgL, SLOT(getImage(char *)));
    connect(rwSocket, SIGNAL(connectedToHost()), ui->widgetImgL, SLOT(writeData()));
    rwThread->start();

}

MainWindow3D::~MainWindow3D()
{
    delete ui;
}

void MainWindow3D::creatActions()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionNetwork, SIGNAL(triggered()), this, SLOT(netsetting()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connectToHost()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnectFromHost()));
}

void MainWindow3D::open()
{
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);

}

void MainWindow3D::loadFile(const QString fileName)
{
    QImage image(fileName);
    QImage rgbImg;
    int imagesize = 0;

    if (image.isNull()) {
        QMessageBox::warning(this, tr("Image"),
                             tr("Cannot open image %1.")
                             .arg(fileName)
                             );
        return;
    }
        
    //emit writeData(imageBuffer);
}

void MainWindow3D::netsetting()
{
    netsettingDialog netsettingDialog(this);
    if (netsettingDialog.exec())
    {
        hostname = netsettingDialog.getHost();
        portid = netsettingDialog.getPort().toInt();
        QMessageBox::warning(this, tr("Network setting"), 
	    tr("network address %1:%2").arg(hostname).arg(portid));
    }
}

void MainWindow3D::connectToHost()
{
    host.hostname = hostname;
    host.portid = portid;

    qDebug() << "invoke the action of connecting to the host";
    emit invokeConnect(&host);
}

void MainWindow3D::disconnectFromHost()
{
    emit invokeDisconnect();
}

void MainWindow3D::displayError(QString *string)
{

    QMessageBox::information(this, tr("Network error"),
                             tr("The following error occurred: %1.")
                             .arg(*string));
}

