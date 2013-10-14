#include "tgt/init.h"
#include "tgt/logmanager.h"
#include "tgt/qt/qtcanvas.h"
#include "tgt/camera.h"
#include "tgt/shadermanager.h"

#include "voreen/core/io/serialization/serialization.h"

#include "core/processors/output/canvasrenderer.h"

#include "ui_mainwindow3d.h"
#include "mainwindow3d.h"
#include "netsettingdialog.h"

MainWindow3D::MainWindow3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3D)
{
    ui->setupUi(this);
    
    creatActions();
    mapCube = new functionCube(this);
    ui->viewerFunc->setCube(mapCube);
    clipbox = new clipBox(this);
    //ui->viewerTran->setBox(clipbox);
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
    connect(this, SIGNAL(invokeConnect(hostAddress *)), rwSocket, SLOT(connectToHost(hostAddress *)));
    connect(this, SIGNAL(invokeDisconnect()), rwSocket, SLOT(disconnectFromHost()));
    connect(ui->widgetImgL, SIGNAL(writeImage(char *)), rwSocket, SLOT(writeImg(char *)));
    connect(ui->widgetImgL, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));
    connect(rwSocket, SIGNAL(imageReady(char *)), ui->widgetImgL, SLOT(getImage(char *)));
    connect(rwSocket, SIGNAL(connectedToHost()), ui->widgetImgL, SLOT(writeData()));
    rwThread->start();

}

MainWindow3D::~MainWindow3D()
{
    delete ui;
    delete workspace;
    delete networkEvaluator;
 
    vapp->deinitializeGL();
    vapp->deinitialize();

}

void MainWindow3D::setVoreenApp(VoreenApplicationQt *app)
{
    vapp = app;
    vapp->initializeGL();
    workspace = new Workspace();
    try {
        workspace->load(VoreenApplication::app()->getResourcePath("workspaces/tools/volumecropping.vws"));
    }
    catch (SerializationException& e) {
        QMessageBox::critical(this, "Loading Workspace Failed", QString::fromStdString(e.what()));
        return;
    }

    // initialize the network evaluator and retrieve the CanvasRenderer processor from the loaded network
    networkEvaluator = new NetworkEvaluator();
    vapp->registerNetworkEvaluator(networkEvaluator);
    network = workspace->getProcessorNetwork();
    std::vector<CanvasRenderer*> canvasRenderer = network->getProcessorsByType<CanvasRenderer>();
    if (canvasRenderer.empty()) {
        QMessageBox::critical(this, "Invalid Workspace", "Loaded workspace does not contain a CanvasRenderer.");
        return;
    }

    // init painter and connect it to canvas, evaluator and canvas renderer
    painter = new VoreenPainter(ui->widgetTran, networkEvaluator, canvasRenderer[0]);
    ui->widgetTran->setPainter(painter);
    canvasRenderer[0]->setCanvas(ui->widgetTran);

    // pass the network to the network evaluator, which also initializes the processors
    networkEvaluator->setProcessorNetwork(network);

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

