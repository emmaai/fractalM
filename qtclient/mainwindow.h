#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QTcpSocket>
#include <QtNetwork>
#include <QImage>
#include <QPen>
#include "typedef.h"
#include "data_socket.h"
#include "functionrect.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     
    hostAddress host;
    unsigned char *imageBuffer;
    unsigned long paramBuffer;
    QPen pen;
    QPointF points[4];

public slots:
    void open();
    void netsetting();
    void displayError(QString *);
    void connectToHost();
    void disconnectFromHost();
    void reconnectToHost();
    void disconnectedByHost();
    void testslot();
    
    void setColorFunction1(QColor *);
    void setColorFunction2(QColor *);
    void setColorFunction3(QColor *);
    void setColorFunction4(QColor *);
    void setColorFunction5(QColor *);
    void setColorFunction6(QColor *);
    void setColorFunction7(QColor *);
    void setColorFunction8(QColor *);
    void setColorFunction9(QColor *);
    void setColorFunctionA(QColor *);

    void setParaFunc1(int);
    void setParaFunc2(int);
    void setParaFunc3(int);
    void setParaFunc4(int);
    void setParaFunc5(int);
    void setParaFunc6(int);
    void setParaFunc7(int);
    void setParaFunc8(int);
    void setParaFunc9(int);
    void setParaFuncA(int);

    void setTransTypeFunc1(int);
    void setTransTypeFunc2(int);
    void setTransTypeFunc3(int);
    void setTransTypeFunc4(int);
    void setTransTypeFunc5(int);
    void setTransTypeFunc6(int);
    void setTransTypeFunc7(int);
    void setTransTypeFunc8(int);
    void setTransTypeFunc9(int);
    void setTransTypeFuncA(int);

    void sendParam();
    void getImage(unsigned char *);

    void coordinateChanged(functionRect *);

signals:
    void invokeConnect(hostAddress *);
    void invokeDisconnect();
    void writeData(unsigned char *);
    void writeParam(char *);
    void funcParamChanged();
    void drawBackground();
    void test();
private:
    Ui::MainWindow *ui;

    void creatActions();
    void loadFile(const QString );
    void uploadImage();

    void setFuncParams(activeFunc *, int);
    void convertCoordinate(nodeCoordinate *, QPointF *);
    void convertPoints(QPointF *, nodeCoordinate *);
    void initialCoordinate();

    QString hostname;
    quint16 portid;
    qint64 blockSize;
    imageSize resolution;
    char *receivemessage;

    activeFunc functionParam[10];
    activeFunc functionParamServer[10];
    int numFunctions;

    functionRect *rect1;
    functionRect *rect2;
    functionRect *rect3;
    functionRect *rect4;
    functionRect *rect5;
    functionRect *rect6;
    functionRect *rect7;
    functionRect *rect8;
    functionRect *rect9;
    functionRect *rectA;

    QGraphicsScene *scene; 
    rwSockData	*rwSocket;
    QThread *rwThread;

};

#endif // MAINWINDOW_H
