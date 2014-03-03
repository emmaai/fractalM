#ifndef VIEWER_H
#define VIEWER_H
#include <QGLViewer/qglviewer.h>
#include "functioncube.h"
#include "clipplane.h"

class Viewer : public QGLViewer
{
    Q_OBJECT
public:
    Viewer(QWidget *parent=0, QGLWidget *shareWidget=0);
    ~Viewer();
    void setCube(functionCube *aCube){if(cube) delete cube; cube = aCube;};
    void setTh(functionTH *aTh){if(Th) delete Th; Th = aTh;};
   // void setBox(clipBox *aBox){if(box) delete box; box = aBox;};
signals:
    void closeTFWindow();
protected :
    virtual void draw();
    virtual void drawWithNames();
    virtual void postSelection(const QPoint& point);
    virtual void postDraw();
    virtual void init();
    virtual QString helpString() const;
    virtual void endSelection(const QPoint& point);
    virtual void enterEvent(QEvent *event);

private :
  void drawCornerAxis();
  functionCube *cube;
  functionTH *Th;
  //clipBox *box;
};

#endif // VIEWER_H
