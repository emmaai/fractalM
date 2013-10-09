#include <QVector3D>
#include <qmath.h>
#include "functioncube.h"
functionCube::functionCube(QObject *parent):QObject(parent)
{
}

functionCube::~functionCube()
{

}

functionEdge::functionEdge(QObject *parent, functionNode *sourceNode, functionNode *destNode):QObject(parent)
{
    source = sourceNode;
    dest = destNode;
    source->addEdge((unsigned long)this);
    dest->addEdge((unsigned long)this);
    setColor(QColor(Qt::black));
}

void functionEdge::setColor(QColor color)
{
    faceColor[0]=color.redF();
    faceColor[1]=color.greenF();
    faceColor[2]=color.blueF();
    faceColor[3]=color.alphaF();
}

functionEdge::~functionEdge()
{
/*
    delete source;
    delete dest;
    */
}

functionNode *functionEdge::sourceNode() const
{
    return source;
}

functionNode *functionEdge::destNode() const
{
    return dest;
}

void functionEdge::adjust()
{
    if(!source || !dest)
	return;
    indices.append(vertices.count());
    vertices.append(source->getCoord());
    indices.append(vertices.count());
    vertices.append(dest->getCoord());
}

void functionEdge::draw()
{
    glPushMatrix();
    QVector4D z(0.0, 0.0, 0.0, 1.0);
    QVector4D p1, p2;
    glLoadMatrixf(source->mat.constData());
    p1 = source->mat *z;
    glLoadMatrixf(dest->mat.constData());
    p2 = dest->mat*z;
    glPopMatrix();

    glLineWidth(3);
    glBegin(GL_LINES);
    //glColor3f(0, 0, 0);
    glVertex3f(p1.x(), p1.y(), p1.z());
    //glColor3f(0, 0, 0);
    glVertex3f(p2.x(), p2.y(), p2.z());
    glEnd();

}


functionNode::functionNode(QObject *parent, QVector3D position):QObject(parent)
{
    setColor(QColor(Qt::darkYellow));
    buildNode(position);
}

functionNode::~functionNode()
{

}

void functionNode::buildNode(QVector3D position)
{
    int rings=101, sectors=101;
    float radius=0.02;
    float subRing = 1.0/(float)(rings-1);
    float subSector = 1.0/(float)(sectors-1);
    float x=0.0, y=0.0, z=0.0;
    for(int r=0; r<rings; r++)
    {
	for(int s=0; s<sectors; s++) 
	{
	    z=sin(-M_PI_2+M_PI*r*subRing);
	    x=cos(2*M_PI*s*subSector)*sin(M_PI*r*subRing);
	    y=sin(2*M_PI*s*subSector)*sin(M_PI*r*subRing);
	    
	    indices.append(r*sectors + s);
	    indices.append(r*sectors + (s+1));
	    indices.append((r+1)*sectors + (s+1));
	    indices.append((r+1)*sectors + s);
	    vertices.append(QVector3D(x*radius, y*radius, z*radius));
	    normals.append(QVector3D(x, y, z));
	}
    
    }

    mat.translate(position);
}

void functionNode::addEdge(unsigned long newEdge)
{
    functionEdge *edge = (functionEdge *)newEdge;
    edgeList << edge;
    edge->adjust();
}

QVector3D functionNode::getCoord()
{
    return coord;
}
void functionNode::setColor(QColor color)
{
    faceColor[0]=color.redF();
    faceColor[1]=color.greenF();
    faceColor[2]=color.blueF();
    faceColor[3]=color.alphaF();
}

void functionNode::draw(GLdouble dx, GLdouble dy, GLdouble dz, GLdouble angle)
{
    coord.setX(dx);
    coord.setY(dy);
    coord.setZ(dz);
    QVector3D z(0.0,0.0,1.0);
    mat.rotate(angle, z);
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
    //glTexCoordPointer(2, GL_FLOAT, 0, texcoords.constData());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glPushMatrix();
    glMultMatrixf(mat.constData());
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);
    const GLushort *glIndices = indices.constData();
    glDrawElements(GL_QUADS, indices.count(), GL_UNSIGNED_SHORT, glIndices);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   
}
