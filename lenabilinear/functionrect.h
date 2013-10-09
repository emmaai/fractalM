#ifndef FUNCTIONRECT
#define FUNCTIONRECT
#include <QGraphicsItem>
#include <QGraphicsObject>
#include "renderframe.h"

class rectEdge;

class rectParts:public QGraphicsObject
{
    Q_OBJECT
public:
    rectParts(QGraphicsItem *parent = 0);

    void addEdge(rectEdge *edge);
    QList<rectEdge *> edges() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF getMoveDis();
    void calculateNewPos();
    void getPen(QPen *);

protected:
     QVariant itemChange(GraphicsItemChange change, const QVariant &value);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);  

signals:
    void itemMoved(rectParts *);

private:
    QList<rectEdge *> edgeList;
    QPointF oldPos;
    graphView *graph;
    QPen pen;
    QPointF moveDis;

};

class rectEdge:public QGraphicsItem
{
public:
    rectEdge(QGraphicsItem *, rectParts *, rectParts *);
    rectParts *sourceNode() const;
    rectParts *destNode() const;

    void adjust();
    void getPen(QPen *);
 
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    rectParts *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    QPen pen;
};

class functionRect:public QGraphicsObject
{
    Q_OBJECT
public:
    functionRect(QGraphicsItem *parent=0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void getPen(QPen *);
    void getBlPoint(QPointF);
    void getBrPoint(QPointF);
    void getTlPoint(QPointF);
    void getTrPoint(QPointF);
    void getTransformType(int);
    QPointF obtainBlPoint();
    QPointF obtainBrPoint();
    QPointF obtainTlPoint();
    QPointF obtainTrPoint();

public slots:
    void recalculateNodes(rectParts *);
signals:
    void pointsChanged(functionRect *);
private:
    QPen pen;
    rectParts *blNode;
    rectParts *brNode;
    rectParts *tlNode;
    rectParts *trNode;
    rectEdge *bEdge;
    rectEdge *lEdge;
    rectEdge *rEdge;
    rectEdge *tEdge;
    int transformType;
};
#endif
