#ifndef FUNCTIONGLWIDGET
#define FUNCTIONGLWIDGET
#include <QGLWidget>
#include "functioncube.h"
#include "qtlogo.h"
class functionGLWidget:public QGLWidget
{
    Q_OBJECT
public:
    functionGLWidget(QWidget *parent=0);
    ~functionGLWidget();
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QColor qtPurple;
    QColor qtGreen;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    functionNode *node[8];
    functionEdge *edge[12];

    functionNode *edgeNode[12];
    functionNode *faceNode[6];
    functionNode *middleNode;

    functionEdge *faceEdge[24];
    functionEdge *innerEdge[6];
};
#endif	
