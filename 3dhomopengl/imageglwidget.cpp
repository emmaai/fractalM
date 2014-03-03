#include <QtWidgets>
#include <QtOpenGL>
#include <math.h>
#include "imageglwidget.h"
imageGLWidget::imageGLWidget(QWidget *parent):QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 45;
    yRot = 45;
    zRot = 0;
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
    qtGreen = QColor::fromCmykF(0.4, 0.0, 1.0, 0.0);
 
    xTParam=0.5;
    yTParam=0.3;
    zTParam=0.25;
    PParam=0.5;
    functionParam.coordinate[0].x = xTParam;
    functionParam.coordinate[1].x = yTParam;
    functionParam.coordinate[2].x = zTParam;
    functionParam.coordinate[3].x = PParam;

    wd=161;
    ht=81;

    count=3*2*(wd-1)*(ht-1);



    svertices=new GLfloat[3*count];
    snormals=new GLfloat[3*count];
    vertices=new GLfloat[3*count];
    normals=new GLfloat[3*count];
    indices=new GLuint[count];

    functionParam.funcNo = 3*count*sizeof(GLfloat);

    int ind=0;
    double pi=3.14159265358979;
    for (int i=0;i<ht-1;i++) {
	for (int j=0;j<wd-1;j++) {
	    svertices[ind++]=0.1*cos(2.0*pi*(j+1)/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*(j+1)/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(2.0*pi*j/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*j/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(2.0*pi*j/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*j/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*cos(pi*(i+1)/(ht-1));

	    svertices[ind++]=0.1*cos(2.0*pi*(j+1)/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*(j+1)/(wd-1))*sin(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(pi*i/(ht-1));
	    svertices[ind++]=0.1*cos(2.0*pi*j/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*j/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*cos(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*cos(2.0*pi*(j+1)/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*sin(2.0*pi*(j+1)/(wd-1))*sin(pi*(i+1)/(ht-1));
	    svertices[ind++]=0.1*cos(pi*(i+1)/(ht-1));
	}
    }
    ind=0;
    double norm[3];
    for (int i=0;i<ht-1;i++) {
	for (int j=0;j<wd-1;j++) {
	    //compute normals via cross products
	    norm[0]=(svertices[ind+4]-svertices[ind+1])*(svertices[ind+8]-svertices[ind+2])
		    -(svertices[ind+5]-svertices[ind+2])*(svertices[ind+7]-svertices[ind+1]);
	    norm[1]=-(svertices[ind+3]-svertices[ind])*(svertices[ind+8]-svertices[ind+2])
		    +(svertices[ind+5]-svertices[ind+2])*(svertices[ind+6]-svertices[ind]);
	    norm[2]=(svertices[ind+3]-svertices[ind])*(svertices[ind+7]-svertices[ind+1])
		    -(svertices[ind+4]-svertices[ind+1])*(svertices[ind+6]-svertices[ind]);
	    double en=sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	    norm[0]=(svertices[ind+4]-svertices[ind+1])*(svertices[ind+8]-svertices[ind+2])
		    -(svertices[ind+5]-svertices[ind+2])*(svertices[ind+7]-svertices[ind+1]);
	    norm[1]=-(svertices[ind+3]-svertices[ind])*(svertices[ind+8]-svertices[ind+2])
		    +(svertices[ind+5]-svertices[ind+2])*(svertices[ind+6]-svertices[ind]);
	    norm[2]=(svertices[ind+3]-svertices[ind])*(svertices[ind+7]-svertices[ind+1])
		    -(svertices[ind+4]-svertices[ind+1])*(svertices[ind+6]-svertices[ind]);
	    en=sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	    snormals[ind++]=norm[0]/en;
	    snormals[ind++]=norm[1]/en;
	    snormals[ind++]=norm[2]/en;
	}
    }

    for (int i=0;i<count;i++) indices[i]=i;
    memcpy((char *)vertices, (char *)svertices, 3*count*sizeof(GLfloat));
    memcpy((char *)normals, (char *)snormals, 3*count*sizeof(GLfloat));

        //emit writeData(imageBuffer);

}

imageGLWidget::~imageGLWidget()
{
//    delete logo;    
    delete vertices;
    delete normals;
    delete indices;
    delete svertices;
    delete snormals;
}

void imageGLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());
/*
    logo = new QtLogo(this, 64);
    logo->setColor(qtGreen.dark());
    */

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
}

void imageGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    //logo->draw();
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    GLfloat fColor[4]={0.5,0.5,0.5,0.5};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, fColor);

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

}
void imageGLWidget::resizeGL(int width, int height)
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

void imageGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void imageGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void imageGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}
 
void imageGLWidget::setXTParam(int value)
{
    //value is 0 to 1000, map onto range 0.45,0.55
    xTParam=0.0001*(value+4500);
    functionParam.coordinate[0].x = xTParam;
    emit writeParam((char *)&functionParam);
    
}

void imageGLWidget::setYTParam(int value)
{
    //value is 0 to 1000, map onto range 0.25,0.35
    yTParam=0.0001*(value+2500);
    functionParam.coordinate[1].x = yTParam;
    emit writeParam((char *)&functionParam);
    
}

void imageGLWidget::setZTParam(int value)
{
    //value is 0 to 1000, map onto range 0.2,0.3
    zTParam=0.0001*(value+2000);
    functionParam.coordinate[2].x = zTParam;
    emit writeParam((char *)&functionParam);
    
}

void imageGLWidget::setPParam(int value)
{
    //value is 0 to 1000, map onto range 0.25,0.75
    PParam=0.0005*(value+500);
    functionParam.coordinate[3].x = PParam;
    emit writeParam((char *)&functionParam);
    
}

void imageGLWidget::writeData()
{

    memcpy(imageBuffer, (char *)&functionParam.funcNo, sizeof(int));
    qDebug() << "image resolution is" << functionParam.funcNo;
    memcpy(imageBuffer+sizeof(int), (char *)svertices, functionParam.funcNo);
    emit writeImage(imageBuffer);

}

void imageGLWidget::getImage(char *image)
{
    memcpy((char *)vertices, image, functionParam.funcNo);
    int ind=0;
    double norm[3];
    for (int i=0;i<ht-1;i++) {
	for (int j=0;j<wd-1;j++) {
	    //compute normals via cross products
	    norm[0]=(vertices[ind+4]-vertices[ind+1])*(vertices[ind+8]-vertices[ind+2])
		    -(vertices[ind+5]-vertices[ind+2])*(vertices[ind+7]-vertices[ind+1]);
	    norm[1]=-(vertices[ind+3]-vertices[ind])*(vertices[ind+8]-vertices[ind+2])
		    +(vertices[ind+5]-vertices[ind+2])*(vertices[ind+6]-vertices[ind]);
	    norm[2]=(vertices[ind+3]-vertices[ind])*(vertices[ind+7]-vertices[ind+1])
		    -(vertices[ind+4]-vertices[ind+1])*(vertices[ind+6]-vertices[ind]);
	    double en=sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	    norm[0]=(vertices[ind+4]-vertices[ind+1])*(vertices[ind+8]-vertices[ind+2])
		    -(vertices[ind+5]-vertices[ind+2])*(vertices[ind+7]-vertices[ind+1]);
	    norm[1]=-(vertices[ind+3]-vertices[ind])*(vertices[ind+8]-vertices[ind+2])
		    +(vertices[ind+5]-vertices[ind+2])*(vertices[ind+6]-vertices[ind]);
	    norm[2]=(vertices[ind+3]-vertices[ind])*(vertices[ind+7]-vertices[ind+1])
		    -(vertices[ind+4]-vertices[ind+1])*(vertices[ind+6]-vertices[ind]);
	    en=sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	    normals[ind++]=norm[0]/en;
	    normals[ind++]=norm[1]/en;
	    normals[ind++]=norm[2]/en;
	}
    }
    updateGL();
}
void imageGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void imageGLWidget::mouseMoveEvent(QMouseEvent *event)
{

}
