#ifndef FUNCTIONCUBE
#define FUNCTIONCUBE
#include <QVector3D>
#include <QVector2D>
#include <QGLWidget>
#include <QMatrix4x4>
#include <QGLViewer/qglviewer.h>

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
