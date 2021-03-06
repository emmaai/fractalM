#ifndef MAINWINDOW3D_H
#define MAINWINDOW3D_H


#include "voreen/core/utils/voreenpainter.h"
#include "voreen/core/network/networkevaluator.h"
#include "voreen/core/network/workspace.h"
#include "voreen/core/network/processornetwork.h"
#include "core/processors/input/volumesource.h"
#include "voreen/qt/voreenapplicationqt.h"
#include "voreen/core/datastructures/volume/volume.h"
#include "voreen/core/datastructures/volume/volumeatomic.h"
#include "voreen/qt/widgets/property/transfuncpropertywidget.h"


#include "tgt/qt/qtcanvas.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include "data_socket.h"
#include "typedef.h"
#include "functioncube.h"
#include "clipplane.h"
#include "viewer.h"

using namespace voreen;

namespace Ui {
class MainWindow3D;
}

class MainWindow3D : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow3D(QWidget *parent = 0);
    ~MainWindow3D();
    void setVoreenApp(VoreenApplicationQt *app);
    hostAddress host;
    unsigned char *imageBuffer;
    unsigned long paramBuffer;
public slots:
    void open();
    void netsetting();
    void displayError(QString *);
    void connectToHost();
    void disconnectFromHost();
    void loadVolume(char *);
    void generateHR();
    void showCrop();
    void cubeMapping();
    void thMapping();
    void showTF();
    void closeTFWindow();
    void savePara();
    void saveClip();

signals:
    void invokeConnect(hostAddress *);
    void invokeDisconnect();
    void writeData(unsigned char *);
    void sendCMD(char *);


    
private:
    Ui::MainWindow3D *ui;

    void creatActions();
    void loadFile(const QString );
    QString hostname;
    quint16 portid;
    rwSockData	*rwSocket;
    QThread *rwThread;
    Viewer *viewerFunc, *viewerFuncO, *viewerFuncTH, *viewerFuncTHO;
    functionCube *mapCube;
    functionCube *mapCubeO;
    functionTH *mapTh, *mapThO;
    clipBox *clipbox;
    VoreenApplicationQt *vapp;
    Workspace* workspace;
    NetworkEvaluator* networkEvaluator;
    ProcessorNetwork* network;
    VoreenPainter* painter, *painterO, *painterC;
    tgt::QtCanvas *sharedContext, *widgetTran, *widgetTranO, *widgetCrop;
    VolumeSource *volume;
    int volumecount;
    unsigned int widthLR, lengthLR, depthLR;
    unsigned int widthHR, lengthHR, depthHR;
    unsigned int clipXMax, clipYMax, clipZMax;
    bool displayHR;
    QProgressDialog  *progress;
    Volume *volumeHandle;
    TransFuncPropertyWidget *tfWidget, *tfWidgetO;
    FloatProperty *clipRight, *clipLeft, *clipFront, *clipBack, *clipBottom, *clipTop;
    bool tfShow;

};

#endif // MAINWINDOW3D_H
