#include "tgt/init.h"
#include "tgt/logmanager.h"
#include "tgt/qt/qtcanvas.h"
#include "tgt/camera.h"
#include "tgt/shadermanager.h"

#include "voreen/core/io/serialization/serialization.h"

#include "core/processors/output/canvasrenderer.h"
 
#include "base/processors/utility/metadataextractor.h"
#include "pvm/io/ddsbase.h" 

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
    mapCube->setFuncNo(2);
    mapCubeO = new functionCube(this);
    mapCubeO->setFuncNo(1);
    ui->viewerFunc->setCube(mapCube);
    ui->viewerFuncO->setCube(mapCubeO);

    //clipbox = new clipBox(this);
    //ui->viewerTran->setBox(clipbox);
    
    volumecount = 0;
    progress=NULL;
    volumeHandle=NULL;
    displayHR = false;
    hostname = "localhost";
    portid = 50000;
    rwSocket = new rwSockData;
    rwThread = new QThread;
    rwSocket->moveToThread(rwThread);
/*
    connect(ui->widgetL, SIGNAL(xRotationChanged(int)), ui->widgetImgL, SLOT(setXRotation(int)));
    connect(ui->widgetL, SIGNAL(yRotationChanged(int)), ui->widgetImgL, SLOT(setYRotation(int)));
    connect(ui->widgetL, SIGNAL(zRotationChanged(int)), ui->widgetImgL, SLOT(setZRotation(int)));

    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setXTParam(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setYTParam(int)));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setZTParam(int)));
    connect(ui->pSlider, SIGNAL(valueChanged(int)), ui->widgetImgL, SLOT(setPParam(int)));
    */

    connect(rwSocket, SIGNAL(rwSockError(QString *)), this, SLOT(displayError(QString *)));
    connect(this, SIGNAL(invokeConnect(hostAddress *)), rwSocket, SLOT(connectToHost(hostAddress *)));
    connect(this, SIGNAL(invokeDisconnect()), rwSocket, SLOT(disconnectFromHost()));

    connect(mapCube, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));
    connect(mapCubeO, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));

    connect(rwSocket, SIGNAL(imageReady(char *)), this, SLOT(loadVolume(char *)));
    connect(this, SIGNAL(sendCMD(char *)), rwSocket, SLOT(sendCMD(char *)));
    /*
    connect(ui->widgetImgL, SIGNAL(writeImage(char *)), rwSocket, SLOT(writeImg(char *)));
    connect(ui->widgetImgL, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));
    connect(rwSocket, SIGNAL(connectedToHost()), ui->widgetImgL, SLOT(writeData()));
    */
    rwThread->start();

}

MainWindow3D::~MainWindow3D()
{
    delete ui;
    delete workspace;
    delete networkEvaluator;
    delete widgetTran;
    delete widgetTranO;
    delete painter;
    delete painterO;

    vapp->deinitializeGL();
    vapp->deinitialize();

}

void MainWindow3D::setVoreenApp(VoreenApplicationQt *app)
{
    vapp = app;
    vapp->initializeGL();

    widgetTranO = new tgt::QtCanvas( "Init Canvas", tgt::ivec2(128, 128), tgt::GLCanvas::RGBADD, ui->splitter, true);
    ui->splitter->addWidget(widgetTranO);
    widgetTran = new tgt::QtCanvas( "Init Canvas", tgt::ivec2(128, 128), tgt::GLCanvas::RGBADD, ui->splitter, true);
    ui->splitter_2->addWidget(widgetTran);

    workspace = new Workspace();
    try {
        workspace->load(VoreenApplication::app()->getResourcePath("workspaces/tools/volumecroppingdouble.vws"));
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
    painter = new VoreenPainter(widgetTran, networkEvaluator, canvasRenderer[0]);
    widgetTran->setPainter(painter);
    canvasRenderer[0]->setCanvas(widgetTran);

    painterO = new VoreenPainter(widgetTranO, networkEvaluator, canvasRenderer[1]);
    widgetTranO->setPainter(painterO);
    canvasRenderer[1]->setCanvas(widgetTranO);
    
   
    // pass the network to the network evaluator, which also initializes the processors
    networkEvaluator->setProcessorNetwork(network);

     MetaDataExtractor *info = (MetaDataExtractor *)network->getProcessorByName("MetaDataExtractor");
    std::string infostring = info->replaceMetaDataAndGetString();
    
    qDebug() << "meta info is" << infostring.c_str();

 
    unsigned int pos = infostring.find("Volume Dimensions");
    pos += 20;
    unsigned int tail = infostring.find(']', pos);
    char *dim = new char[tail-pos+1];
    infostring.copy(dim, tail-pos, pos); 
    qDebug() << "found dimensions " << pos;
    qDebug() << "found tail " << tail;
    dim[tail-pos] = '\0';
    qDebug() << "dimension is " << dim;

    QString diminfo(dim);
    QStringList list = diminfo.split(" ");
    qDebug () << "dim list" << list;
    widthLR = (unsigned int)list.at(0).toUInt();
    lengthLR = (unsigned int)list.at(1).toUInt();
    depthLR = (unsigned int)list.at(2).toUInt();
    qDebug () << "dim is" << widthLR << lengthLR << depthLR;
    delete dim;

    info = (MetaDataExtractor *)network->getProcessorByName("MetaDataExtractor 2");
    infostring = info->replaceMetaDataAndGetString();
    pos = infostring.find("Volume Dimensions");
    pos += 20;
    tail = infostring.find(']', pos);
    dim = new char[tail-pos+1];
    infostring.copy(dim, tail-pos, pos); 
    qDebug() << "found dimensions " << pos;
    qDebug() << "found tail " << tail;
    dim[tail-pos] = '\0';
    qDebug() << "dimension is " << dim;

    diminfo.clear();
    //diminfo.resize(tail-pos+1);
    diminfo.insert(0, QString(dim));
    qDebug() << "diminfo is " << diminfo;
    list.clear();
    list = diminfo.split(" ");
    qDebug () << "dim list" << list;
    widthHR = (unsigned int)list.at(0).toUInt();
    lengthHR = (unsigned int)list.at(1).toUInt();
    depthHR = (unsigned int)list.at(2).toUInt();
    qDebug () << "dim is" << widthHR << lengthHR << depthHR;
    delete dim;



}

void MainWindow3D::loadVolume(char* buffer)
{
    VolumeRAM *dataset = 0;

    if(displayHR)
    {

	imageBuffer = new unsigned char[widthHR*lengthHR*depthHR];
	progress->setValue(66);
	progress->setLabelText("Recieving data...");
	memcpy(imageBuffer, (unsigned char *)buffer, widthHR*lengthHR*depthHR);
    }
    else
    {
	imageBuffer = new unsigned char[widthLR*lengthLR*depthLR];
	memcpy(imageBuffer, (unsigned char *)buffer, widthLR*lengthLR*depthLR);
    }
    char *filename = "resource/volumes/volume2.pvm";
    /*
    writePVMvolume(filename, imageBuffer,
                     width, length, depth, 1, 1.f, 1.f, 1.f,
                    NULL, NULL, NULL, NULL);
		    */
   //if(volumecount == 0)
    {

	if(displayHR)
	{

	    progress->setValue(88);
	    progress->setLabelText("Rendering...");
	    dataset = new VolumeRAM_UInt8(imageBuffer, tgt::ivec3(widthHR, lengthHR, depthHR));	
	}
	else
	    dataset = new VolumeRAM_UInt8(imageBuffer, tgt::ivec3(widthLR, lengthLR, depthLR));	

	qDebug() << "new dataset";
	volume = (VolumeSource *)network->getProcessorByName("VolumeSource");
	qDebug() << "volume  is " << volume;
	volume->clearVolume();
	volumeHandle = new Volume(dataset, tgt::vec3(1, 1, 1), tgt::vec3(0.0f));
	qDebug() << "volume handle is " << volumeHandle;
	volume->setVolume(volumeHandle, true);
	if(displayHR)
	{
	    displayHR = false;
	    progress->setValue(99);
	}
    }

}

void MainWindow3D::creatActions()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionNetwork, SIGNAL(triggered()), this, SLOT(netsetting()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connectToHost()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnectFromHost()));
    connect(ui->actionHR, SIGNAL(triggered()), this, SLOT(generateHR()));
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

void MainWindow3D::generateHR()
{
    int cmdSize = 2;
    if(progress)
    {
	delete progress;
    }
    progress = new QProgressDialog(this);
    progress->setCancelButton(0);
    progress->setWindowModality(Qt::WindowModal);
    progress->setRange(0, 99);
    progress->setWindowTitle("Generating Hight Resolution Data");
    char *cmd = new char[sizeof(cmdSize) + cmdSize];
    memcpy(cmd, (char *)&cmdSize, sizeof(cmdSize));
    memcpy(cmd+sizeof(cmdSize), "HR", cmdSize);
    emit sendCMD(cmd);    
    displayHR = true;
    progress->setValue(33);
    progress->setLabelText("Waiting for finishing transformation...");
}
