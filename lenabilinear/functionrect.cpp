#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <cmath>
#include "functionrect.h"
//class rectParts
rectParts::rectParts(QGraphicsItem *parent):QGraphicsObject(parent)
{
     setFlag(ItemIsMovable);
     setFlag(ItemSendsGeometryChanges);
     setCacheMode(DeviceCoordinateCache);
    // setZValue(-1);
}

void rectParts::addEdge(rectEdge *edge)
{
    edgeList << edge;
    edge->adjust();
}
 
QList<rectEdge *> rectParts::edges() const
{
    return edgeList;
}

QRectF rectParts::boundingRect() const
{
    qreal adjust=2;
    return QRectF(-10-adjust, -10-adjust, 23+adjust, 23+adjust);
}

QPainterPath rectParts::shape() const
{
    QPainterPath path;
    path.addEllipse(-10,-10, 20, 20);
    return path;
}

void rectParts::calculateNewPos()
{
 
    

}
QPointF rectParts::getMoveDis()
{
    return moveDis;
}

void rectParts::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
	gradient.setCenter(3, 3);
	gradient.setFocalPoint(3, 3);
	gradient.setColorAt(1, QColor(Qt::yellow).light(120));
	gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
	gradient.setColorAt(0, Qt::yellow);
	gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    painter->setPen(pen);
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant rectParts::itemChange(GraphicsItemChange change, const QVariant &value)
{
 
    switch (change) {
	 case ItemPositionHasChanged:
	    moveDis = pos()-oldPos;
	    oldPos = pos();
	    foreach (rectEdge *edge, edgeList)
		 edge->adjust();
	    
	    if(scene()&&scene()->mouseGrabberItem() == this)
	    {
		qDebug() << "node moved by mouse";
		 emit itemMoved(this);
	    }
	     break;
	 default:
	     break;
     };

     return QGraphicsItem::itemChange(change, value);
}

void rectParts::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     update();
     QGraphicsItem::mousePressEvent(event);
}

void rectParts::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
 
    update();
    QGraphicsItem::mouseReleaseEvent(event);

}

void rectParts::getPen(QPen *functionpen)
{
    pen = *functionpen;
}

//class rectEdge
rectEdge::rectEdge(QGraphicsItem *parent, rectParts *sourceNode, rectParts *destNode):QGraphicsItem(parent)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}
 
rectParts *rectEdge::sourceNode() const
{
    return source;
}

rectParts *rectEdge::destNode() const
{
    return dest;
}

void rectEdge::adjust()
{
 
    if (!source || !dest)
	return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
       QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
       sourcePoint = line.p1() + edgeOffset;
       destPoint = line.p2() - edgeOffset;
    } else 
    {
       sourcePoint = destPoint = line.p1();
    }
}

QRectF rectEdge::boundingRect() const
{
     if (!source || !dest)
         return QRectF();

     qreal penWidth = 1;
     qreal extra = penWidth/ 2.0;

     return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                       destPoint.y() - sourcePoint.y()))
         .normalized()
         .adjusted(-extra, -extra, extra, extra);
}

void rectEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(pen);
    painter->drawLine(line);

}

void rectEdge::getPen(QPen *functionpen)
{
    pen = *functionpen;
}

//class functionRect
functionRect::functionRect(QGraphicsItem *parent)
{
    //setFlag(ItemHasNoContents);
    blNode = new rectParts(this);
    brNode = new rectParts(this);
    trNode = new rectParts(this);
    tlNode = new rectParts(this);
    bEdge = new rectEdge(this, blNode, brNode);
    lEdge = new rectEdge(this, blNode, tlNode);
    rEdge = new rectEdge(this, brNode, trNode);
    tEdge = new rectEdge(this, tlNode, trNode);
    connect(blNode, SIGNAL(itemMoved(rectParts *)), this, SLOT(recalculateNodes(rectParts *)));
    connect(brNode, SIGNAL(itemMoved(rectParts *)), this, SLOT(recalculateNodes(rectParts *)));
    connect(trNode, SIGNAL(itemMoved(rectParts *)), this, SLOT(recalculateNodes(rectParts *)));
    connect(tlNode, SIGNAL(itemMoved(rectParts *)), this, SLOT(recalculateNodes(rectParts *)));
}

QRectF functionRect::boundingRect() const
{
    return QRectF();
}

void functionRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void functionRect::getPen(QPen *functionpen)
{
    pen = *functionpen;
    blNode->getPen(&pen);
    brNode->getPen(&pen);
    tlNode->getPen(&pen);
    trNode->getPen(&pen);
    bEdge->getPen(&pen);
    lEdge->getPen(&pen);
    rEdge->getPen(&pen);
    tEdge->getPen(&pen);
    blNode->update();
    brNode->update();
    tlNode->update();
    trNode->update();
    
}

void functionRect::getBlPoint(QPointF point)
{
    QPointF functionPoint;
    functionPoint = mapFromScene(point);
    if(blNode->pos()== functionPoint)
	return;
    blNode->setPos(functionPoint);
}

void functionRect::getBrPoint(QPointF point)
{
    QPointF functionPoint;
    functionPoint = mapFromScene(point);
    brNode->setPos(functionPoint);
    brNode->update();

}

void functionRect::getTrPoint(QPointF point)
{
    QPointF functionPoint;
    functionPoint = mapFromScene(point);
    if(trNode->pos() == functionPoint)
	return;
    trNode->setPos(functionPoint);
    trNode->update();

}

void functionRect::getTlPoint(QPointF point)
{
    QPointF functionPoint;
    functionPoint = mapFromScene(point);
    tlNode->setPos(functionPoint);
    tlNode->update();

}

QPointF functionRect::obtainBlPoint()
{
    return blNode->pos(); 
}

QPointF functionRect::obtainBrPoint()
{
    return brNode->pos(); 
}

QPointF functionRect::obtainTlPoint()
{
    return tlNode->pos(); 
}

QPointF functionRect::obtainTrPoint()
{
    return trNode->pos(); 
}

void functionRect::getTransformType(int type) 
{
    transformType = type;
}

void functionRect::recalculateNodes(rectParts *node)
{
    QPointF dis = node->getMoveDis();
    QPointF oldDist, dist, lDist;
    double oldLength, oldCosTheta, oldSinTheta,  cosTheta, sinTheta,
	cosDiff, sinDiff, length, dxt, dyt, lLength, cosAlpha, sinAlpha, cosSum, sinSum;
    qDebug() << "move dis is" << dis;
    if(node==blNode)
    {
	    brNode->setPos(brNode->pos()+dis);
	    trNode->setPos(trNode->pos()+dis);
	    tlNode->setPos(tlNode->pos()+dis);
    }
    if(node==brNode)
    {
	oldDist = brNode->pos()-dis-blNode->pos(); 
	oldLength =sqrt(pow(oldDist.x(), 2)+pow(oldDist.y(), 2));
	oldCosTheta = (oldDist.x())/oldLength;
	oldSinTheta = (-oldDist.y())/oldLength;
	
	dist = brNode->pos()-blNode->pos();
	length =sqrt(pow(dist.x(), 2)+pow(dist.y(), 2));
	cosTheta = (dist.x())/length;
	sinTheta = (-dist.y())/length;
	cosDiff = cosTheta*oldCosTheta+sinTheta*oldSinTheta;
	sinDiff = sinTheta*oldCosTheta-cosTheta*oldSinTheta;

	lDist = tlNode->pos() - blNode->pos();
	lLength =sqrt(pow(lDist.x(), 2)+pow(lDist.y(), 2));
	cosAlpha = lDist.x()/lLength;
	sinAlpha = -lDist.y()/lLength;
	cosSum = cosAlpha*cosDiff - sinAlpha*sinDiff;
	sinSum = sinAlpha*cosDiff + cosAlpha*sinDiff;
	if(oldLength <= 0.01)
	{
	    tlNode->setPos(blNode->pos().x()-(brNode->pos().y()-blNode->pos().y()), 
		blNode->pos().y()+(brNode->pos().x()-blNode->pos().x()));
	}else
	{
	    tlNode->setPos(blNode->pos().x()+lLength * length/oldLength*(cosSum), 
		blNode->pos().y()-lLength*length/oldLength*sinSum);
	}

	switch(transformType) 
	{
	    case 1:
	    case 2:
		
		    trNode->setPos(tlNode->pos().x()+brNode->pos().x()-blNode->pos().x(), 
			tlNode->pos().y()+brNode->pos().y()-blNode->pos().y());
		break;
	    case 3:
	    case 4:
		lDist = trNode->pos() - blNode->pos();
		lLength =sqrt(pow(lDist.x(), 2)+pow(lDist.y(), 2));
		cosAlpha = lDist.x()/lLength;
		sinAlpha = -lDist.y()/lLength;
		cosSum = cosAlpha*cosDiff - sinAlpha*sinDiff;
		sinSum = sinAlpha*cosDiff + cosAlpha*sinDiff;
		if(oldLength <= 0.01)
		{
		     trNode->setPos(tlNode->pos().x()+brNode->pos().x()-blNode->pos().x(), 
			tlNode->pos().y()+brNode->pos().y()-blNode->pos().y());

		}else
		{
		    trNode->setPos(blNode->pos().x()+lLength * length/oldLength*(cosSum), 
			blNode->pos().y()-lLength*length/oldLength*sinSum);
		}
		break;
	    default:
		break;

	}//switch(transformType)
    }//if(node==brNode)
    if(node == trNode)
    {
	switch(transformType)
	{
	    case 1:
		tlNode->setPos(blNode->pos().x()+trNode->pos().x()-brNode->pos().x(), 
		    blNode->pos().y()+trNode->pos().y()-brNode->pos().y());
		break;
	    case 2:
		oldDist = trNode->pos()-dis-blNode->pos(); 
		oldLength =sqrt(pow(oldDist.x(), 2)+pow(oldDist.y(), 2));
		oldCosTheta = (oldDist.x())/oldLength;
		oldSinTheta = (-oldDist.y())/oldLength;
		
		dist = trNode->pos()-blNode->pos();
		length =sqrt(pow(dist.x(), 2)+pow(dist.y(), 2));
		cosTheta = (dist.x())/length;
		sinTheta = (-dist.y())/length;
		cosDiff = cosTheta*oldCosTheta+sinTheta*oldSinTheta;
		sinDiff = sinTheta*oldCosTheta-cosTheta*oldSinTheta;

		lDist = tlNode->pos() - blNode->pos();
		lLength =sqrt(pow(lDist.x(), 2)+pow(lDist.y(), 2));
		cosAlpha = lDist.x()/lLength;
		sinAlpha = -lDist.y()/lLength;
		cosSum = cosAlpha*cosDiff - sinAlpha*sinDiff;
		sinSum = sinAlpha*cosDiff + cosAlpha*sinDiff;

		if(oldLength <= 0.01)
		{
		    tlNode->setPos(blNode->pos().x()+(trNode->pos().x()-blNode->pos().x())/2-(trNode->pos().y()-blNode->pos().y())/2,
			blNode->pos().y()+(trNode->pos().x()-blNode->pos().x())/2+(trNode->pos().y()-blNode->pos().y())/2);
		}else
		{
		    tlNode->setPos(blNode->pos().x()+lLength * length/oldLength*(cosSum), 
			blNode->pos().y()-lLength*length/oldLength*sinSum);
		}
		lDist = brNode->pos() - blNode->pos();
		lLength =sqrt(pow(lDist.x(), 2)+pow(lDist.y(), 2));
		cosAlpha = lDist.x()/lLength;
		sinAlpha = -lDist.y()/lLength;
		cosSum = cosAlpha*cosDiff - sinAlpha*sinDiff;
		sinSum = sinAlpha*cosDiff + cosAlpha*sinDiff;
		if(oldLength <= 0.01)
		{
		     brNode->setPos(blNode->pos().x()+trNode->pos().x()-tlNode->pos().x(), 
			blNode->pos().y()+trNode->pos().y()-tlNode->pos().y());

		}else
		{
		    brNode->setPos(blNode->pos().x()+lLength * length/oldLength*(cosSum), 
			blNode->pos().y()-lLength*length/oldLength*sinSum);
		}

		break;
	    case 3:
	    case 4:
		break;
	    default:
		break;
	} //switch(transformType)
   
    }//if(node == trNode)
    if(node == tlNode)
    {
	switch(transformType)
	{
	    case 1:
		trNode->setPos(tlNode->pos().x()+brNode->pos().x()-blNode->pos().x(), 
			tlNode->pos().y()+brNode->pos().y()-blNode->pos().y());
		break;
	    case 2:
		oldDist = tlNode->pos()-dis-blNode->pos(); 
		oldLength =sqrt(pow(oldDist.x(), 2)+pow(oldDist.y(), 2));
		oldCosTheta = (oldDist.x())/oldLength;
		oldSinTheta = (-oldDist.y())/oldLength;
		
		dist = tlNode->pos()-blNode->pos();
		length =sqrt(pow(dist.x(), 2)+pow(dist.y(), 2));
		cosTheta = (dist.x())/length;
		sinTheta = (-dist.y())/length;
		cosDiff = cosTheta*oldCosTheta+sinTheta*oldSinTheta;
		sinDiff = sinTheta*oldCosTheta-cosTheta*oldSinTheta;

		lDist = brNode->pos() - blNode->pos();
		lLength =sqrt(pow(lDist.x(), 2)+pow(lDist.y(), 2));
		cosAlpha = lDist.x()/lLength;
		sinAlpha = -lDist.y()/lLength;
		cosSum = cosAlpha*cosDiff - sinAlpha*sinDiff;
		sinSum = sinAlpha*cosDiff + cosAlpha*sinDiff;

		if(oldLength <= 0.01)
		{
		    brNode->setPos(blNode->pos().x()+(trNode->pos().y()-blNode->pos().y()),
			blNode->pos().y()-(trNode->pos().y()-blNode->pos().y()));
		}else
		{
		    brNode->setPos(blNode->pos().x()+lLength * length/oldLength*(cosSum), 
			blNode->pos().y()-lLength*length/oldLength*sinSum);
		}
		trNode->setPos(tlNode->pos().x()+brNode->pos().x()-blNode->pos().x(), 
			tlNode->pos().y()+brNode->pos().y()-blNode->pos().y());
	    case 3:
	    case 4:
		trNode->setPos(trNode->pos()+dis);
		break;
	    }//switch(transformType)

    }// if(node == tlNode)

    emit pointsChanged(this);
}
