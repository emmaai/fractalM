#include <QtWidgets>
#include <QtOpenGL>
#include <math.h>
#include "functionglwidget.h"
 
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

functionGLWidget::functionGLWidget(QWidget *parent):QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 45;
    yRot = 45;
    zRot = 0;
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    qtGreen = QColor::fromCmykF(0.4, 0.0, 1.0, 0.0);
}

functionGLWidget::~functionGLWidget()
{
    int i;
    for(i=0; i<8; i++)
	delete node[i];
    for(i=0; i<12; i++)
	delete edge[i];
    for(i=0; i<12; i++)
	delete edgeNode[i];
    for(i=0; i<6; i++)
	delete faceNode[i];
    for(i=0; i<24; i++)
	delete faceEdge[i];
    delete middleNode;
    for(i=0; i<6; i++)
	delete innerEdge[i];
    
}

void functionGLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    int i;
    QVector3D v[8]={
	QVector3D(-0.25, -0.25, -0.25),
	QVector3D(0.25, -0.25, -0.25),
	QVector3D(0.25, 0.25, -0.25),
	QVector3D(-0.25, 0.25, -0.25),
	QVector3D(-0.25, 0.25, 0.25),
	QVector3D(0.25, 0.25, 0.25),
	QVector3D(0.25, -0.25, 0.25),
	QVector3D(-0.25, -0.25, 0.25)
    };
    for(i=0; i<8; i++)
	node[i] = new functionNode(this, v[i]);

    edge[0] = new functionEdge(this, node[0], node[1]);
    edge[1] = new functionEdge(this, node[1], node[2]);
    edge[2] = new functionEdge(this, node[2], node[3]);
    edge[3] = new functionEdge(this, node[3], node[0]);
    edge[4] = new functionEdge(this, node[4], node[5]);
    edge[5] = new functionEdge(this, node[5], node[6]);
    edge[6] = new functionEdge(this, node[6], node[7]);
    edge[7] = new functionEdge(this, node[7], node[4]);
    edge[8] = new functionEdge(this, node[0], node[7]);
    edge[9] = new functionEdge(this, node[1], node[6]);
    edge[10] = new functionEdge(this, node[2], node[5]);
    edge[11] = new functionEdge(this, node[3], node[4]);

    QVector3D ve[12]={
	QVector3D(0, -0.25, -0.25),
	QVector3D(0.25, 0, -0.25),
	QVector3D(0, 0.25, -0.25),
	QVector3D(-0.25, 0, -0.25),
	QVector3D(-0.25, 0, 0.25),
	QVector3D(0, 0.25, 0.25),
	QVector3D(0.25, 0, 0.25),
	QVector3D(0, -0.25, 0.25),
	QVector3D(-0.25, -0.25, 0),
	QVector3D(0.25, -0.25, 0),
	QVector3D(0.25, 0.25, 0),
	QVector3D(-0.25, 0.25, 0)
    };

    for(i=0; i<12; i++)
    {
	edgeNode[i] = new functionNode(this, ve[i]); 
	edgeNode[i]->setColor(QColor(Qt::green));
    
    }

    QVector3D vf[6]={
	QVector3D(0, 0, -0.25),
	QVector3D(0, 0, 0.25),
	QVector3D(0, -0.25, 0),
	QVector3D(0.25, 0, 0),
	QVector3D(0, 0.25, 0),
	QVector3D(-0.25, 0, 0)
    
    };

    for(i=0; i<6; i++)
    {
	faceNode[i] = new functionNode(this, vf[i]); 
	faceNode[i]->setColor(QColor(Qt::green));
    }

    middleNode = new functionNode(this, QVector3D(0, 0, 0));    
    middleNode->setColor(QColor(Qt::blue));

    faceEdge[0] = new functionEdge(this, faceNode[0], edgeNode[0]);
    faceEdge[1] = new functionEdge(this, faceNode[0], edgeNode[1]);
    faceEdge[2] = new functionEdge(this, faceNode[0], edgeNode[2]);
    faceEdge[3] = new functionEdge(this, faceNode[0], edgeNode[3]);
    faceEdge[4] = new functionEdge(this, faceNode[1], edgeNode[4]);
    faceEdge[5] = new functionEdge(this, faceNode[1], edgeNode[5]);
    faceEdge[6] = new functionEdge(this, faceNode[1], edgeNode[6]);
    faceEdge[7] = new functionEdge(this, faceNode[1], edgeNode[7]);
    faceEdge[8] = new functionEdge(this, faceNode[2], edgeNode[0]);
    faceEdge[9] = new functionEdge(this, faceNode[2], edgeNode[9]);
    faceEdge[10] = new functionEdge(this, faceNode[2], edgeNode[7]);
    faceEdge[11] = new functionEdge(this, faceNode[2], edgeNode[8]);
    faceEdge[12] = new functionEdge(this, faceNode[3], edgeNode[1]);
    faceEdge[13] = new functionEdge(this, faceNode[3], edgeNode[10]);
    faceEdge[14] = new functionEdge(this, faceNode[3], edgeNode[6]);
    faceEdge[15] = new functionEdge(this, faceNode[3], edgeNode[9]);
    faceEdge[16] = new functionEdge(this, faceNode[4], edgeNode[2]);
    faceEdge[17] = new functionEdge(this, faceNode[4], edgeNode[10]);
    faceEdge[18] = new functionEdge(this, faceNode[4], edgeNode[5]);
    faceEdge[19] = new functionEdge(this, faceNode[4], edgeNode[11]);
    faceEdge[20] = new functionEdge(this, faceNode[5], edgeNode[3]);
    faceEdge[21] = new functionEdge(this, faceNode[5], edgeNode[11]);
    faceEdge[22] = new functionEdge(this, faceNode[5], edgeNode[4]);
    faceEdge[23] = new functionEdge(this, faceNode[5], edgeNode[8]);

    for(i=0; i<6; i++)
    {
	innerEdge[i] = new functionEdge(this, middleNode, faceNode[i]);
    }

}

void functionGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    int i;
    for(i=0; i<8; i++)
	node[i]->draw(0, 0, 0, 0);
    for(i=0; i<12; i++)
	edge[i]->draw();
    for(i=0; i<12; i++)
	edgeNode[i]->draw(0, 0, 0, 0);
    for(i=0; i<6; i++)
	faceNode[i]->draw(0, 0, 0, 0);
    for(i=0; i<24; i++)
	faceEdge[i]->draw();
    middleNode->draw(0, 0, 0, 0);
    for(i=0; i<6; i++)
	innerEdge[i]->draw();
}
void functionGLWidget::resizeGL(int width, int height)
{    
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360 )
        angle -= 360;
}

void functionGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void functionGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void functionGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void functionGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void functionGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
