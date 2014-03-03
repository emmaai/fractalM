#ifndef IMAGEGLWIDGET
#define IMAGEGLWIDGET
#include <QGLWidget>
#include "qtlogo.h"
#include "typedef.h"
class imageGLWidget:public QGLWidget
{
    Q_OBJECT
public:
    imageGLWidget(QWidget *parent=0);
    ~imageGLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
 
    void setXTParam(int value);
    void setYTParam(int value);
    void setZTParam(int value);
    void setPParam(int value);

    void getImage(char *);
    void writeData();
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void writeParam(char *);
    void writeImage(char *);

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
    QtLogo *logo;

    activeFunc functionParam;

    int wd,ht;

    int count;

    GLfloat *vertices;
    GLfloat *normals;
    GLuint *indices;

    GLfloat *svertices;
    GLfloat *snormals;

    double xTParam,yTParam,zTParam,PParam;
    char imageBuffer[3*1024*1024+sizeof(int)];
};

#endif //IMAGEGLWIDGET
