#ifndef FUNCTIONCUBE
#define FUNCTIONCUBE
#include <QVector3D>
#include <QVector2D>
#include <QGLWidget>
#include <QMatrix4x4>
#include <QGLViewer/qglviewer.h>
#include "typedef.h"

class functionNode;
class functionEdge;

class functionCube:public QObject
{
    Q_OBJECT
public:
    explicit functionCube(QObject *parent = 0);
    ~functionCube();
    void draw(bool names=false);
    qglviewer::ManipulatedFrame* frame(unsigned short i){return frame_[i];};
    void setSelectedFrameNumber(unsigned short nb){ selected = nb;};
    void setFuncNo(int no){int i=0; for(i=0; i<PARANUMBER; i++) functionParam[i].funcNo = no;};
    void saveParam(QString filename);
    void writeCurrentParam();

signals:
    void writeParam(char *);
private:
    void setColor(unsigned short nb);
    qglviewer::ManipulatedFrame* frame_[19];
    unsigned short selected;
    functionNode *node[8];
    functionEdge *edge[12];

    functionNode *edgeNode[12];
    functionNode *faceNode[6];
    functionNode *middleNode;

    functionEdge *faceEdge[24];
    functionEdge *innerEdge[6];
    activeFunc functionParam[PARANUMBER];
    QVector3D points[27];
    unsigned long samePoint;
};

class functionTH:public QObject
{
    Q_OBJECT
public:
    explicit functionTH(QObject *parent=0);
    ~functionTH();
    void draw(bool names=false);
    qglviewer::ManipulatedFrame* frame(unsigned short i){return frame_[i];};
    void setSelectedFrameNumber(unsigned short nb){ selected = nb;};
    void setFuncNo(int no){int i=0; for(i=0; i<PARANUMBER; i++) functionParam[i].funcNo = no;};
    void saveParam(QString filename);
    void writeCurrentParam();
    void setEmbeddingMode(unsigned int mode){embeddingMode = mode;};

signals:
    void writeParam(char *);

private:
    void setColor(unsigned short nb);
    qglviewer::ManipulatedFrame* frame_[19];
    unsigned short selected;
    functionNode *node[4];
    functionEdge *edge[6];

    functionNode *edgeNode[6];
    functionNode *middleNode;

    functionEdge *faceEdge[12];
    functionEdge *innerEdge;

    activeFunc functionParam[PARANUMBER];
    QVector3D points[10], lastPos[6], vertices[4];
    double lAB, lAC, lAD, lBC, lBD, lCD;
    double rAB, rAC, rAD, rBC, rBD, rCD;
    unsigned long samePoint;
    unsigned int embeddingMode;
    void calPoints();
    void calRatio();
};

class functionEdge:public QObject
{
    Q_OBJECT
public:
    explicit functionEdge(QObject *, functionNode *, functionNode *);
    ~functionEdge();
    void draw(GLdouble, GLdouble, GLdouble, GLdouble);
    functionNode *sourceNode() const;
    functionNode *destNode() const;

    void adjust();
    void setColor(QColor color);
    void draw();
private:
    functionNode *source, *dest;
    QVector<QVector3D> vertices;
    QVector<GLushort> indices;
    GLfloat faceColor[4];

};

class functionNode:public QObject
{
    Q_OBJECT
public:
    explicit functionNode(QObject *parent, QVector3D position);
    ~functionNode();
    void draw(GLdouble, GLdouble, GLdouble, GLdouble);
    void setColor(QColor color);
    void addEdge(unsigned long);
    QVector3D getCoord();
    QMatrix4x4 mat;
private:
    void buildNode(QVector3D);
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<QVector2D> texcoords;
    QVector<GLushort> indices;
    GLfloat faceColor[4];
    QList<functionEdge *> edgeList;
    QVector3D coord;

};
#endif
