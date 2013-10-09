#include "renderframe.h"
#include <QPainter>
#include <QDebug>
#include <algorithm>
#include <QKeyEvent>
 

graphView::graphView(QWidget *parent)
     : QGraphicsView(parent)
{

}

void graphView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        //centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        //centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        //centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        //centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void graphView::itemMoved()
{

}
 
void graphView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void graphView::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
    /*
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
	    */
    }
}

void graphView::zoomIn()
{
    scaleView(qreal(1.2));
}

void graphView::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
