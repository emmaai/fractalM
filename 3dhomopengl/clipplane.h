#ifndef CLIPPLANE_H
#define CLIPPLANE_H
#include <QGLViewer/vec.h>
#include <QGLViewer/manipulatedFrame.h>
#include <QMatrix4x4>
class clipBox:public QObject
{
    Q_OBJECT
public:
    explicit clipBox(QObject *parent=0);
    ~clipBox();
    void draw(bool names=false);
    qglviewer::ManipulatedFrame *frame(unsigned short i){return frame_[i];};
    void setSelectedFrameNumber(unsigned short nb){selected=nb;};
    GLuint boxTexture();
    void enablePlane();
    void initBox(float, float, float);
private:
    void setColor(unsigned short nb, float transparency);
    qglviewer::ManipulatedFrame *frame_[6];
    unsigned short selected;
    void drawPlane(qglviewer::Vec, int, float, float);
    void drawLine(qglviewer::Vec, qglviewer::Vec,qglviewer::Vec,qglviewer::Vec);
    float width, length, height;
    GLuint m_boxTexture;
};


#endif // CLIPPLANE_H
