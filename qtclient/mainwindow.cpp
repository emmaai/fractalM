#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "netsettingdialog.h"
#include "data_socket.h"
#include <QLabel>
#include <QMutexLocker>
#include <QColorDialog>
#include <QColor>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    creatActions();
    hostname = "localhost";
    portid = 50000;
    blockSize = 32768*8;
    receivemessage = new char[blockSize];
    imageBuffer = new unsigned char[3*1024*1024+sizeof(int)];
    paramBuffer = (unsigned long)functionParamServer;
    numFunctions = 0;
    resolution.xLength = 512;
    resolution.yWidth = 512;

    rwSocket = new rwSockData;
    rwThread = new QThread;
    rwSocket->moveToThread(rwThread);
    qDebug() << "mainwindow:  current thread " << this->thread();
    qDebug() << "rwSocket parent is" << rwSocket->parent();

    pen.setWidth(2);
    scene = new QGraphicsScene(ui->frameFunction); 
    scene->setSceneRect(-200, -200, 400, 400);
    scene->addRect(scene->sceneRect(), QPen(Qt::black, 3));
    ui->frameFunction->setScene(scene);
    ui->frameFunction->setCacheMode(QGraphicsView::CacheBackground);
    ui->frameFunction->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->frameFunction->setRenderHint(QPainter::Antialiasing);
    ui->frameFunction->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->frameFunction->scale(qreal(0.8), qreal(0.8));
    ui->frameFunction->setMinimumSize(400, 400);

    rect1= new functionRect; 
    rect2= new functionRect; 
    rect3= new functionRect; 
    rect4= new functionRect; 
    rect5= new functionRect; 
    rect6= new functionRect; 
    rect7= new functionRect; 
    rect8= new functionRect; 
    rect9= new functionRect; 
    rectA= new functionRect; 
    initialCoordinate();
    
    ui->labelColor1->setColor(QColor::fromRgb(170,0,255));
    ui->labelColor2->setColor(QColor::fromRgb(255,255,127));
    ui->labelColor3->setColor(QColor::fromRgb(170,255,0));
    ui->labelColor4->setColor(QColor::fromRgb(255,0,127));
    ui->labelColor5->setColor(QColor::fromRgb(255,127,0));
    ui->labelColor6->setColor(QColor::fromRgb(0,127,255));
    ui->labelColor7->setColor(QColor::fromRgb(255,170,127));
    ui->labelColor8->setColor(QColor::fromRgb(255,170,255));
    ui->labelColor9->setColor(QColor::fromRgb(85,255,255));
    ui->labelColor10->setColor(QColor::fromRgb(255,0,255));
    //connect(tcpSocket, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(rect1, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect2, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect3, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect4, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect5, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect6, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect7, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect8, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rect9, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));
    connect(rectA, SIGNAL(pointsChanged(functionRect *)), this, SLOT(coordinateChanged(functionRect *)));

    connect(rwSocket, SIGNAL(rwSockError(QString *)), this, SLOT(displayError(QString *)));
    connect(this, SIGNAL(invokeConnect(hostAddress *)), rwSocket, SLOT(connectToHost(hostAddress *)));
    connect(this, SIGNAL(invokeDisconnect()), rwSocket, SLOT(disconnectFromHost()));
    connect(this, SIGNAL(writeData(unsigned char *)), rwSocket, SLOT(writeImg(unsigned char *)));
    connect(this, SIGNAL(writeParam(char *)), rwSocket, SLOT(writeParam(char *)));
    connect(this, SIGNAL(funcParamChanged()), this, SLOT(sendParam()));
        //connect(this, SIGNAL(drawBackground()), ui->frameFunction, SLOT(drawBackground()));
    connect(rwSocket, SIGNAL(finished()), rwThread, SLOT(quit()));
    connect(rwSocket, SIGNAL(imageReady(unsigned char *)), this, SLOT(getImage(unsigned char *)));
    rwThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::creatActions()
{
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionNetwork, SIGNAL(triggered()), this, SLOT(netsetting()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connectToHost()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnectFromHost()));

    connect(ui->labelColor1, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction1(QColor *)));
    connect(ui->labelColor2, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction2(QColor *)));
    connect(ui->labelColor3, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction3(QColor *)));
    connect(ui->labelColor4, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction4(QColor *)));
    connect(ui->labelColor5, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction5(QColor *)));
    connect(ui->labelColor6, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction6(QColor *)));
    connect(ui->labelColor7, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction7(QColor *)));
    connect(ui->labelColor8, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction8(QColor *)));
    connect(ui->labelColor9, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunction9(QColor *)));
    connect(ui->labelColor10, SIGNAL(colorSelected(QColor *)), this, SLOT(setColorFunctionA(QColor *)));

    connect(ui->checkBoxf01, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc1(int )));
    connect(ui->checkBoxf02, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc2(int )));
    connect(ui->checkBoxf03, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc3(int )));
    connect(ui->checkBoxf04, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc4(int )));
    connect(ui->checkBoxf05, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc5(int )));
    connect(ui->checkBoxf06, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc6(int )));
    connect(ui->checkBoxf07, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc7(int )));
    connect(ui->checkBoxf08, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc8(int )));
    connect(ui->checkBoxf09, SIGNAL(stateChanged(int )), this, SLOT(setParaFunc9(int )));
    connect(ui->checkBoxf10, SIGNAL(stateChanged(int )), this, SLOT(setParaFuncA(int )));

    connect(ui->comboBoxTransfmType1, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc1(int)));
    connect(ui->comboBoxTransfmType2, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc2(int)));
    connect(ui->comboBoxTransfmType3, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc3(int)));
    connect(ui->comboBoxTransfmType4, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc4(int)));
    connect(ui->comboBoxTransfmType5, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc5(int)));
    connect(ui->comboBoxTransfmType6, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc6(int)));
    connect(ui->comboBoxTransfmType7, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc7(int)));
    connect(ui->comboBoxTransfmType8, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc8(int)));
    connect(ui->comboBoxTransfmType9, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFunc9(int)));
    connect(ui->comboBoxTransfmType10, SIGNAL(currentIndexChanged(int)), this, SLOT(setTransTypeFuncA(int)));

    
}

void MainWindow::open()
{
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);

}

void MainWindow::loadFile(const QString fileName)
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
        
    ui->labelImg->setPixmap(QPixmap::fromImage(image));
    ui->labelImg->adjustSize();
    rgbImg = image.convertToFormat(QImage::Format_RGB888);
    imagesize = rgbImg.width()*rgbImg.height()*3;
    resolution.xLength = rgbImg.width();
    resolution.yWidth = rgbImg.height();
    memcpy(imageBuffer, (unsigned char *)&imagesize, sizeof(int));
    qDebug() << "image resolution is" << imageBuffer;
    memcpy(imageBuffer+sizeof(int), rgbImg.bits(), rgbImg.width()*rgbImg.height()*3);
    //emit writeData(imageBuffer);
}

void MainWindow::getImage(unsigned char *image)
{
    qDebug() << "get the image";
    unsigned long ptr = (unsigned long)imageBuffer+sizeof(int); 
    /*
    char buf[32768*8];
    qint64 lineLength;
    QFile file("image.bmp");
    if (file.open(QFile::ReadOnly)) {
	qDebug() << "read file";
	while(!file.atEnd())
	{
	    lineLength = file.read(buf, sizeof(buf));
	    memcpy((char *)ptr, buf, lineLength);
	    ptr += lineLength;
	    qDebug() << "read size is" << lineLength;
	}
    }else
    {
	qDebug() << "cannot open the file"; 
    }
    */
    memcpy(imageBuffer+sizeof(int), image, resolution.xLength*resolution.yWidth*3);
    QImage transformImage(imageBuffer+sizeof(int), resolution.xLength,resolution.yWidth, QImage::Format_RGB888);
    ui->labelImg->setPixmap(QPixmap::fromImage(transformImage));
    ui->labelImg->adjustSize();

}
void MainWindow::netsetting()
{
    netsettingDialog netsettingDialog(this);
    if (netsettingDialog.exec())
    {
        hostname = netsettingDialog.getHost();
        portid = netsettingDialog.getPort().toInt();
        QMessageBox::warning(this, tr("Network setting"), tr("network address %1:%2").arg(hostname).arg(portid));
    }
}

void MainWindow::initialCoordinate()
{
    activeFunc *function = functionParam;
    for(int i=3;i>0;i--)
    {
	function->funcNo = 0;
	function->coordinate[0].x=0.0;
	function->coordinate[0].y=0.0;
	function->coordinate[1].x=0.5;
	function->coordinate[1].y=0.0;
	function->coordinate[2].x=0.5;
	function->coordinate[2].y=0.5;
	function->coordinate[3].x=0.0;
	function->coordinate[3].y=0.5;
	function++;
	function->funcNo = 0;
	function->coordinate[0].x=0.25;
	function->coordinate[0].y=0.5;
	function->coordinate[1].x=0.75;
	function->coordinate[1].y=0.5;
	function->coordinate[2].x=0.75;
	function->coordinate[2].y=1;
	function->coordinate[3].x=0.25;
	function->coordinate[3].y=1.0;
	function++;
	function->funcNo = 0;
	function->coordinate[0].x=0.5;
	function->coordinate[0].y=0.0;
	function->coordinate[1].x=1.0;
	function->coordinate[1].y=0.0;
	function->coordinate[2].x=1.0;
	function->coordinate[2].y=0.5;
	function->coordinate[3].x=0.5;
	function->coordinate[3].y=0.5;
	function++;
    }
    function->funcNo = 0;
    function->coordinate[0].x=0.0;
    function->coordinate[0].y=0.0;
    function->coordinate[1].x=0.5;
    function->coordinate[1].y=0.0;
    function->coordinate[2].x=0.5;
    function->coordinate[2].y=0.5;
    function->coordinate[3].x=0.0;
    function->coordinate[3].y=0.5;

    QList<rectParts *> nodes;
    nodeCoordinate center;
    center.x = 0.25;
    center.y = 0.25;
    convertCoordinate(&center,&points[0]);
    rect1->setPos(points[0]);
    rect4->setPos(points[0]);
    rect7->setPos(points[0]);
    rectA->setPos(points[0]);
    foreach(QGraphicsItem *item, rect1->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[0].coordinate[i], &points[2]);
	nodes[i]->setPos(rect1->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect4->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[3].coordinate[i], &points[2]);
	nodes[i]->setPos(rect4->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect7->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[6].coordinate[i], &points[2]);
	nodes[i]->setPos(rect7->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rectA->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[9].coordinate[i], &points[2]);
	nodes[i]->setPos(rectA->mapFromScene(points[2]));
    }
    nodes.clear();
    center.x = 0.75;
    center.y = 0.25;
    convertCoordinate(&center,&points[0]);
    rect3->setPos(points[0]);
    rect6->setPos(points[0]);
    rect9->setPos(points[0]);
    foreach(QGraphicsItem *item, rect3->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[2].coordinate[i], &points[2]);
	nodes[i]->setPos(rect3->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect6->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[5].coordinate[i], &points[2]);
	nodes[i]->setPos(rect6->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect9->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[8].coordinate[i], &points[2]);
	nodes[i]->setPos(rect9->mapFromScene(points[2]));
    }
    nodes.clear();
    center.x = 0.5;
    center.y = 0.75;
    convertCoordinate(&center,&points[0]);
    rect2->setPos(points[0]);
    rect5->setPos(points[0]);
    rect8->setPos(points[0]);
    foreach(QGraphicsItem *item, rect2->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[1].coordinate[i], &points[2]);
	nodes[i]->setPos(rect2->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect5->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[4].coordinate[i], &points[2]);
	nodes[i]->setPos(rect5->mapFromScene(points[2]));
    }
    nodes.clear();
    foreach(QGraphicsItem *item, rect8->childItems())
    {
	if(rectParts *node = qgraphicsitem_cast<rectParts *>(item))
	    nodes << node;
    }
    for(int i=0;i<4;i++)
    {
	convertCoordinate(&functionParam[7].coordinate[i], &points[2]);
	nodes[i]->setPos(rect8->mapFromScene(points[2]));
    }
    nodes.clear();
}

void MainWindow::setColorFunction1(QColor *colorFunc)
{
    unsigned long pointPtr = (unsigned long)points;
    functionParam[0].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[0].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[0].colorMap.blue = (unsigned char)colorFunc->blue();
    pen.setColor(ui->labelColor1->palette().color(ui->labelColor1->backgroundRole()));
    //ui->frameFunction->getPen(&pen);
    convertCoordinate(&functionParam[0].coordinate[0], &points[0]);
    convertCoordinate(&functionParam[0].coordinate[1], &points[1]);
    convertCoordinate(&functionParam[0].coordinate[2], &points[2]);
    convertCoordinate(&functionParam[0].coordinate[3], &points[3]);
    //ui->frameFunction->getPoints((char *)pointPtr);
    //ui->frameFunction->update();

    emit funcParamChanged();
}

void MainWindow::setColorFunction2(QColor *colorFunc)
{
    functionParam[1].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[1].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[1].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();
}

void MainWindow::setColorFunction3(QColor *colorFunc)
{
    functionParam[2].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[2].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[2].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();
}

void MainWindow::setColorFunction4(QColor *colorFunc)
{
    functionParam[3].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[3].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[3].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setColorFunction5(QColor *colorFunc)
{
    functionParam[4].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[4].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[4].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();
}

void MainWindow::setColorFunction6(QColor *colorFunc)
{
    functionParam[5].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[5].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[5].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setColorFunction7(QColor *colorFunc)
{
    functionParam[6].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[6].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[6].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setColorFunction8(QColor *colorFunc)
{
    functionParam[7].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[7].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[7].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setColorFunction9(QColor *colorFunc)
{
    functionParam[8].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[8].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[8].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setColorFunctionA(QColor *colorFunc)
{
    functionParam[9].colorMap.red = (unsigned char)colorFunc->red();
    functionParam[9].colorMap.green = (unsigned char)colorFunc->green();
    functionParam[9].colorMap.blue = (unsigned char)colorFunc->blue();
    emit funcParamChanged();

}

void MainWindow::setTransTypeFunc1(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect1->getTransformType(1);
	    functionParam[0].transType = 1;
	    break;
	case 1://similitude
	    rect1->getTransformType(2);
	    functionParam[0].transType = 2;
	    break;
	case 2: //projective
	    rect1->getTransformType(3);
	    functionParam[0].transType = 3;
	    break;
	case 3: //bilinear
	    rect1->getTransformType(4);
	    functionParam[0].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc2(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect2->getTransformType(1);
	    functionParam[1].transType = 1;
	    break;
	case 1://similitude
	    rect2->getTransformType(2);
	    functionParam[1].transType = 2;
	    break;
	case 2: //projective
	    rect2->getTransformType(3);
	    functionParam[1].transType = 3;
	    break;
	case 3: //bilinear
	    rect2->getTransformType(4);
	    functionParam[1].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc3(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect3->getTransformType(1);
	    functionParam[2].transType = 1;
	    break;
	case 1://similitude
	    rect3->getTransformType(1);
	    functionParam[2].transType = 2;
	    break;
	case 2: //projective
	    rect3->getTransformType(1);
	    functionParam[2].transType = 3;
	    break;
	case 3: //bilinear
	    rect3->getTransformType(1);
	    functionParam[2].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc4(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect4->getTransformType(1);
	    functionParam[3].transType = 1;
	    break;
	case 1://similitude
	    rect4->getTransformType(2);
	    functionParam[3].transType = 2;
	    break;
	case 2: //projective
	    rect4->getTransformType(3);
	    functionParam[3].transType = 3;
	    break;
	case 3: //bilinear
	    rect4->getTransformType(4);
	    functionParam[3].transType = 4;
	    break;
	default:
	    break;
    }//switch
    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc5(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect5->getTransformType(1);
	    functionParam[4].transType = 1;
	    break;
	case 1://similitude
	    rect5->getTransformType(2);
	    functionParam[4].transType = 2;
	    break;
	case 2: //projective
	    rect5->getTransformType(3);
	    functionParam[4].transType = 3;
	    break;
	case 3: //bilinear
	    rect5->getTransformType(4);
	    functionParam[4].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc6(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect6->getTransformType(1);
	    functionParam[5].transType = 1;
	    break;
	case 1://similitude
	    rect6->getTransformType(2);
	    functionParam[5].transType = 2;
	    break;
	case 2: //projective
	    rect6->getTransformType(3);
	    functionParam[5].transType = 3;
	    break;
	case 3: //bilinear
	    rect6->getTransformType(4);
	    functionParam[5].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc7(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect7->getTransformType(1);
	    functionParam[6].transType = 1;
	    break;
	case 1://similitude
	    rect7->getTransformType(2);
	    functionParam[6].transType = 2;
	    break;
	case 2: //projective
	    rect7->getTransformType(3);
	    functionParam[6].transType = 3;
	    break;
	case 3: //bilinear
	    rect7->getTransformType(4);
	    functionParam[6].transType = 4;
	    break;
	default:
	    break;
    }//switch
    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc8(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect8->getTransformType(1);
	    functionParam[7].transType = 1;
	    break;
	case 1://similitude
	    rect8->getTransformType(2);
	    functionParam[7].transType = 2;
	    break;
	case 2: //projective
	    rect8->getTransformType(3);
	    functionParam[7].transType = 3;
	    break;
	case 3: //bilinear
	    rect8->getTransformType(4);
	    functionParam[7].transType = 4;
	    break;
	default:
	    break;
    }//switch
    emit funcParamChanged();
}

void MainWindow::setTransTypeFunc9(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rect9->getTransformType(1);
	    functionParam[8].transType = 1;
	    break;
	case 1://similitude
	    rect9->getTransformType(2);
	    functionParam[8].transType = 2;
	    break;
	case 2: //projective
	    rect9->getTransformType(3);
	    functionParam[8].transType = 3;
	    break;
	case 3: //bilinear
	    rect9->getTransformType(4);
	    functionParam[8].transType = 4;
	    break;
	default:
	    break;
    }//switch
    emit funcParamChanged();
}

void MainWindow::setTransTypeFuncA(int currentindex)
{
    switch(ui->comboBoxTransfmType1->currentIndex())
    {
	case 0: //Affine
	    rectA->getTransformType(1);
	    functionParam[9].transType = 1;
	    break;
	case 1://similitude
	    rectA->getTransformType(2);
	    functionParam[9].transType = 2;
	    break;
	case 2: //projective
	    rectA->getTransformType(3);
	    functionParam[9].transType = 3;
	    break;
	case 3: //bilinear
	    rectA->getTransformType(4);
	    functionParam[9].transType = 4;
	    break;
	default:
	    break;
    }//switch

    emit funcParamChanged();
}

void MainWindow::setParaFunc1(int state)
{
    unsigned long pointPtr = (unsigned long)points;
    if(ui->checkBoxf01->isChecked())
    {
	setFuncParams(&functionParam[0], 1);
	ui->comboBoxTransfmType1->setEnabled(true);
	ui->labelColor1->setEnabled(true);
	pen.setColor(ui->labelColor1->palette().color(ui->labelColor1->backgroundRole()));
	rect1->getPen(&pen);
	qDebug() << "scene pos is" << points[0];
	scene->addItem(rect1);
	functionParam[0].funcNo = 1;
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect1);
	functionParam[0].funcNo = 0;
	ui->comboBoxTransfmType1->setEnabled(false);
	ui->labelColor1->setEnabled(false);
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc2(int state)
{
    
    unsigned long pointPtr = (unsigned long)points;
    if(ui->checkBoxf02->isChecked())
    {
	ui->comboBoxTransfmType2->setEnabled(true);
	ui->labelColor2->setEnabled(true);
	pen.setColor(ui->labelColor2->palette().color(ui->labelColor2->backgroundRole()));
	rect2->getPen(&pen);
	scene->addItem(rect2);
	functionParam[1].funcNo = 2;
	setFuncParams(&functionParam[1], 2);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect2);
	ui->comboBoxTransfmType2->setEnabled(false);
	ui->labelColor2->setEnabled(false);
	functionParam[1].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc3(int state)
{
    
    if(ui->checkBoxf03->isChecked())
    {
	ui->comboBoxTransfmType3->setEnabled(true);
	ui->labelColor3->setEnabled(true);
	pen.setColor(ui->labelColor3->palette().color(ui->labelColor3->backgroundRole()));
	rect3->getPen(&pen);
	scene->addItem(rect3);

	functionParam[2].funcNo = 3;
	setFuncParams(&functionParam[2], 3);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect3);
	ui->comboBoxTransfmType3->setEnabled(false);
	ui->labelColor3->setEnabled(false);
	functionParam[2].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc4(int state)
{
    
    if(ui->checkBoxf04->isChecked())
    {
	ui->comboBoxTransfmType4->setEnabled(true);
	ui->labelColor4->setEnabled(true);
	pen.setColor(ui->labelColor4->palette().color(ui->labelColor4->backgroundRole()));
	rect4->getPen(&pen);
	scene->addItem(rect4);

	functionParam[3].funcNo = 4;
	setFuncParams(&functionParam[3], 4);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect4);
	ui->comboBoxTransfmType4->setEnabled(false);
	ui->labelColor4->setEnabled(false);
	functionParam[3].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc5(int state)
{
    
    if(ui->checkBoxf05->isChecked())
    {
	ui->comboBoxTransfmType5->setEnabled(true);
	ui->labelColor5->setEnabled(true);
	pen.setColor(ui->labelColor5->palette().color(ui->labelColor5->backgroundRole()));
	rect5->getPen(&pen);
	scene->addItem(rect5);

	functionParam[4].funcNo = 5;
	setFuncParams(&functionParam[4], 5);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect5);
	ui->comboBoxTransfmType5->setEnabled(false);
	ui->labelColor5->setEnabled(false);
	functionParam[4].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc6(int state)
{
    
    if(ui->checkBoxf06->isChecked())
    {
	ui->comboBoxTransfmType6->setEnabled(true);
	ui->labelColor6->setEnabled(true);
	pen.setColor(ui->labelColor6->palette().color(ui->labelColor6->backgroundRole()));
	rect6->getPen(&pen);
	scene->addItem(rect6);

	functionParam[5].funcNo = 6;
	setFuncParams(&functionParam[5], 6);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect6);
	ui->comboBoxTransfmType2->setEnabled(false);
	ui->labelColor6->setEnabled(false);
	functionParam[5].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc7(int state)
{
    
    if(ui->checkBoxf07->isChecked())
    {
	ui->comboBoxTransfmType7->setEnabled(true);
	ui->labelColor7->setEnabled(true);
	pen.setColor(ui->labelColor7->palette().color(ui->labelColor7->backgroundRole()));
	rect7->getPen(&pen);
	scene->addItem(rect7);

	functionParam[6].funcNo = 7;
	setFuncParams(&functionParam[6], 7);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect7);
	ui->comboBoxTransfmType7->setEnabled(false);
	ui->labelColor7->setEnabled(false);
	functionParam[6].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc8(int state)
{
    
    if(ui->checkBoxf08->isChecked())
    {
	ui->comboBoxTransfmType8->setEnabled(true);
	ui->labelColor8->setEnabled(true);
	pen.setColor(ui->labelColor8->palette().color(ui->labelColor8->backgroundRole()));
	rect8->getPen(&pen);
	scene->addItem(rect8);

	functionParam[7].funcNo = 8;
	setFuncParams(&functionParam[7], 8);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect8);
	ui->comboBoxTransfmType8->setEnabled(false);
	ui->labelColor8->setEnabled(false);
	functionParam[7].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFunc9(int state)
{
    
    if(ui->checkBoxf09->isChecked())
    {
	ui->comboBoxTransfmType9->setEnabled(true);
	ui->labelColor9->setEnabled(true);
	pen.setColor(ui->labelColor9->palette().color(ui->labelColor9->backgroundRole()));
	rect9->getPen(&pen);
	scene->addItem(rect9);

	functionParam[8].funcNo = 9;
	setFuncParams(&functionParam[8], 9);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rect9);
	ui->comboBoxTransfmType9->setEnabled(false);
	ui->labelColor9->setEnabled(false);
	functionParam[8].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setParaFuncA(int state)
{
    
    if(ui->checkBoxf10->isChecked())
    {
	ui->comboBoxTransfmType10->setEnabled(true);
	ui->labelColor10->setEnabled(true);
	pen.setColor(ui->labelColor10->palette().color(ui->labelColor10->backgroundRole()));
	rectA->getPen(&pen);
	scene->addItem(rectA);

	functionParam[9].funcNo = 10;
	setFuncParams(&functionParam[9], 10);
	numFunctions++; 
    }
    else
    {
	scene->removeItem(rectA);
	ui->comboBoxTransfmType10->setEnabled(false);
	ui->labelColor10->setEnabled(false);
	functionParam[9].funcNo = 0;
	numFunctions--;
    }
    emit funcParamChanged();
}

void MainWindow::setFuncParams(activeFunc *function, int checkedBox)
{
    QPalette  palette;
    QColor color;
    switch (checkedBox)
    {
	case 1:
	    switch(ui->comboBoxTransfmType1->currentIndex())
	    {
		case 0: //Affine
		    rect1->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect1->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect1->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect1->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor1->palette().color(ui->labelColor1->backgroundRole());
	    	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs01->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }

	    break;
	case 2:
	    switch(ui->comboBoxTransfmType2->currentIndex())
	    {
		case 0: //Affine
		    rect2->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect2->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect2->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect2->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor2->palette().color(ui->labelColor2->backgroundRole());
	    	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs02->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 3:
	    switch(ui->comboBoxTransfmType3->currentIndex())
	    {
		case 0: //Affine
		    rect3->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect3->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect3->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect3->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor3->palette().color(ui->labelColor3->backgroundRole());
	    	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs03->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 4:
	    switch(ui->comboBoxTransfmType4->currentIndex())
	    {
		case 0: //Affine
		    rect4->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect4->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect4->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect4->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor4->palette().color(ui->labelColor4->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs04->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }

	    break;
	case 5:
	    switch(ui->comboBoxTransfmType5->currentIndex())
	    {
		case 0: //Affine
		    rect5->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect5->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect5->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect5->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor5->palette().color(ui->labelColor5->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs05->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 6:
	    switch(ui->comboBoxTransfmType6->currentIndex())
	    {
		case 0: //Affine
		    rect6->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect6->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect6->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect6->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor6->palette().color(ui->labelColor6->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs06->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 7:
	    switch(ui->comboBoxTransfmType7->currentIndex())
	    {
		case 0: //Affine
		    rect7->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect7->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect7->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect7->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor7->palette().color(ui->labelColor7->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs07->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 8:
	    switch(ui->comboBoxTransfmType8->currentIndex())
	    {
		case 0: //Affine
		    rect8->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect8->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect8->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect8->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor8->palette().color(ui->labelColor8->backgroundRole());
		if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs08->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 9:
	    switch(ui->comboBoxTransfmType9->currentIndex())
	    {
		case 0: //Affine
		    rect9->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rect9->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rect9->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rect9->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor9->palette().color(ui->labelColor9->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs09->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	case 10:
	    switch(ui->comboBoxTransfmType10->currentIndex())
	    {
		case 0: //Affine
		    rectA->getTransformType(1);
		    function->transType = 1;
		    break;
		case 1://similitude
		    rectA->getTransformType(2);
		    function->transType = 2;
		    break;
		case 2: //projective
		    rectA->getTransformType(3);
		    function->transType = 3;
		    break;
		case 3: //bilinear
		    rectA->getTransformType(4);
		    function->transType = 4;
		    break;
		default:
		    break;
	    }//switch
	    
	    color = ui->labelColor10->palette().color(ui->labelColor10->backgroundRole());
	    if(ui->fixProbsCheckBox->isChecked())
		function->prob = -1.0;
	    else
	    {
		function->prob = (float)ui->lineEditProbs10->text().toDouble(); 
		if(function->prob <0)
		    function->prob = 0;
		else if(function->prob>1)
		    function->prob = 1;
	    }
	    break;
	default:
	    break;
    
    }//switch(checkedBox)
    function->resolution.xLength = resolution.xLength;
    function->resolution.yWidth = resolution.yWidth;
    function->colorMap.red = (unsigned char)color.red();
    function->colorMap.green = (unsigned char)color.green();
    function->colorMap.blue = (unsigned char)color.blue();
}

void MainWindow::convertCoordinate(nodeCoordinate *nodes, QPointF *points)
{
    int scale = scene->width();
    points->setX((nodes->x*scale)-200);
    points->setY(scale-200-(nodes->y*scale));
    qDebug() << "convert points is" << *points;
}


void MainWindow::convertPoints(QPointF * points, nodeCoordinate *nodes)
{
    int scale = scene->width();
    nodes->x = (points->x()+200)/scale;
    nodes->y = (scale-200-points->y())/scale;
    qDebug() << "convert coordinate is" << nodes->x << nodes->y;
}

void MainWindow::coordinateChanged(functionRect *rect)
{
    nodeCoordinate node[4]; 
    QPointF point[4];
    point[0] = rect->obtainBlPoint();
    point[1] = rect->obtainBrPoint();
    point[2] = rect->obtainTrPoint();
    point[3] = rect->obtainTlPoint();

    for(int i=0; i<4; i++)
    {
	convertPoints(&point[i], &node[i]);	 
    }

    if(rect==rect1)
    {
	functionParam[0].coordinate[0].x=node[0].x;
	functionParam[0].coordinate[0].y=node[0].y;
	functionParam[0].coordinate[1].x=node[1].x;
	functionParam[0].coordinate[1].y=node[1].y;
	functionParam[0].coordinate[2].x=node[2].x;
	functionParam[0].coordinate[2].y=node[2].y;
	functionParam[0].coordinate[3].x=node[3].x;
	functionParam[0].coordinate[3].y=node[3].y;
    }
    if(rect==rect2)
    {
	functionParam[1].coordinate[0].x=node[0].x;
	functionParam[1].coordinate[0].y=node[0].y;
	functionParam[1].coordinate[1].x=node[1].x;
	functionParam[1].coordinate[1].y=node[1].y;
	functionParam[1].coordinate[2].x=node[2].x;
	functionParam[1].coordinate[2].y=node[2].y;
	functionParam[1].coordinate[3].x=node[3].x;
	functionParam[1].coordinate[3].y=node[3].y;
    }
    if(rect==rect3)
    {
	functionParam[2].coordinate[0].x=node[0].x;
	functionParam[2].coordinate[0].y=node[0].y;
	functionParam[2].coordinate[1].x=node[1].x;
	functionParam[2].coordinate[1].y=node[1].y;
	functionParam[2].coordinate[2].x=node[2].x;
	functionParam[2].coordinate[2].y=node[2].y;
	functionParam[2].coordinate[3].x=node[3].x;
	functionParam[2].coordinate[3].y=node[3].y;
    }
    if(rect==rect4)
    {
	functionParam[3].coordinate[0].x=node[0].x;
	functionParam[3].coordinate[0].y=node[0].y;
	functionParam[3].coordinate[1].x=node[1].x;
	functionParam[3].coordinate[1].y=node[1].y;
	functionParam[3].coordinate[2].x=node[2].x;
	functionParam[3].coordinate[2].y=node[2].y;
	functionParam[3].coordinate[3].x=node[3].x;
	functionParam[3].coordinate[3].y=node[3].y;
    }
    if(rect==rect5)
    {
	functionParam[4].coordinate[0].x=node[0].x;
	functionParam[4].coordinate[0].y=node[0].y;
	functionParam[4].coordinate[1].x=node[1].x;
	functionParam[4].coordinate[1].y=node[1].y;
	functionParam[4].coordinate[2].x=node[2].x;
	functionParam[4].coordinate[2].y=node[2].y;
	functionParam[4].coordinate[3].x=node[3].x;
	functionParam[4].coordinate[3].y=node[3].y;
    }
    if(rect==rect6)
    {
	functionParam[5].coordinate[0].x=node[0].x;
	functionParam[5].coordinate[0].y=node[0].y;
	functionParam[5].coordinate[1].x=node[1].x;
	functionParam[5].coordinate[1].y=node[1].y;
	functionParam[5].coordinate[2].x=node[2].x;
	functionParam[5].coordinate[2].y=node[2].y;
	functionParam[5].coordinate[3].x=node[3].x;
	functionParam[5].coordinate[3].y=node[3].y;
    }
    if(rect==rect7)
    {
	functionParam[6].coordinate[0].x=node[0].x;
	functionParam[6].coordinate[0].y=node[0].y;
	functionParam[6].coordinate[1].x=node[1].x;
	functionParam[6].coordinate[1].y=node[1].y;
	functionParam[6].coordinate[2].x=node[2].x;
	functionParam[6].coordinate[2].y=node[2].y;
	functionParam[6].coordinate[3].x=node[3].x;
	functionParam[6].coordinate[3].y=node[3].y;
    }
    if(rect==rect8)
    {
	functionParam[7].coordinate[0].x=node[0].x;
	functionParam[7].coordinate[0].y=node[0].y;
	functionParam[7].coordinate[1].x=node[1].x;
	functionParam[7].coordinate[1].y=node[1].y;
	functionParam[7].coordinate[2].x=node[2].x;
	functionParam[7].coordinate[2].y=node[2].y;
	functionParam[7].coordinate[3].x=node[3].x;
	functionParam[7].coordinate[3].y=node[3].y;
    }
    if(rect==rect9)
    {
	functionParam[8].coordinate[0].x=node[0].x;
	functionParam[8].coordinate[0].y=node[0].y;
	functionParam[8].coordinate[1].x=node[1].x;
	functionParam[8].coordinate[1].y=node[1].y;
	functionParam[8].coordinate[2].x=node[2].x;
	functionParam[8].coordinate[2].y=node[2].y;
	functionParam[8].coordinate[3].x=node[3].x;
	functionParam[8].coordinate[3].y=node[3].y;
    }
    if(rect==rectA)
    {
	functionParam[9].coordinate[0].x=node[0].x;
	functionParam[9].coordinate[0].y=node[0].y;
	functionParam[9].coordinate[1].x=node[1].x;
	functionParam[9].coordinate[1].y=node[1].y;
	functionParam[9].coordinate[2].x=node[2].x;
	functionParam[9].coordinate[2].y=node[2].y;
	functionParam[9].coordinate[3].x=node[3].x;
	functionParam[9].coordinate[3].y=node[3].y;
    }

    emit funcParamChanged(); 
}

void MainWindow::sendParam()
{

    unsigned long bufferPtr=paramBuffer;
    int i=0;
    memset((char *)paramBuffer, 0, 10*sizeof(activeFunc));
    for(i=0; i<10; i++)
    {
	if(functionParam[i].funcNo)
	{
	    qDebug() << "numFucntions is" << numFunctions;
	    functionParam[i].numActiveFuncs = numFunctions;	
	    memcpy((char *)bufferPtr, &functionParam[i], sizeof(activeFunc));
	    bufferPtr += sizeof(activeFunc);
	}
    }
    emit writeParam((char *)paramBuffer);
}

void MainWindow::connectToHost()
{
    host.hostname = hostname;
    host.portid = portid;

    qDebug() << "invoke the action of connecting to the host";
    emit invokeConnect(&host);
}

void MainWindow::disconnectFromHost()
{
    emit invokeDisconnect();
}

void MainWindow::disconnectedByHost()
{
    QMessageBox::information(this, tr("Network"),
                             tr("Disconnected by host")
                             );

}

void MainWindow::reconnectToHost()
{

}

void MainWindow::displayError(QString *string)
{

    QMessageBox::information(this, tr("Network error"),
                             tr("The following error occurred: %1.")
                             .arg(*string));
}



void MainWindow::testslot()
{
    qDebug() << "this is a test of signal";
}

