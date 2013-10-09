#ifndef RENDERFRAME
#define RENDERFRAME
#include <QLabel>
#include <QPen>
#include <QPixmap>
#include <QGraphicsView>

class graphView:public QGraphicsView
{
    Q_OBJECT
public:
    graphView(QWidget *parent=0);
    void itemMoved();
public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void scaleView(qreal scaleFactor);
protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif
