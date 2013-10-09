#ifndef VIEWER_H
#define VIEWER_H
#include <QGLViewer/qglviewer.h>
#include "functioncube.h"
#include "clipplane.h"

class Viewer : public QGLViewer
{
    Q_OBJECT
public:
    Viewer(QWidget *parent=0);
    ~Viewer();
    void setCube(functionCube *aCube){if(cube) delete cube; cube = aCube;};
    void setBox(clipBox *aBox){if(box) delete box; box = aBox;};
protected :
    virtual void draw();
    virtual void drawWithNames();
    virtual void postSelection(const QPoint& point);
    virtual void postDraw();
    virtual void init();
    virtual QString helpString() const;

private :
  void drawCornerAxis();
  functionCube *cube;
  clipBox *box;
};

#endif // VIEWER_H
