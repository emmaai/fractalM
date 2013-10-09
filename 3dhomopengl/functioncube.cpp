#include <QVector3D>
#include <qmath.h>
#include "functioncube.h"
using namespace qglviewer;
functionCube::functionCube(QObject *parent):QObject(parent)
{
    int i;
    for(i=0;i<19;i++)
    {
	frame_[i] = new ManipulatedFrame(); 
	/*
	if(i>0)
	    frame(i)->setReferenceFrame(frame(i-1));
	    */
    }
 
/*
    LocalConstraint* edgeConstraint = new LocalConstraint();
    edgeConstraint->setTranslationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    */
 

    WorldConstraint* edgeConstraintX = new WorldConstraint();
    edgeConstraintX->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    edgeConstraintX->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(0.0,1.0,0.0));

    WorldConstraint* edgeConstraintY = new WorldConstraint();
    edgeConstraintY->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    edgeConstraintY->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(1.0,0.0,0.0));

    WorldConstraint* edgeConstraintZ = new WorldConstraint();
    edgeConstraintZ->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    edgeConstraintZ->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(0.0,0.0,1.0));

    WorldConstraint* faceConstraintX = new WorldConstraint();
    faceConstraintX->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    faceConstraintX->setTranslationConstraint(AxisPlaneConstraint::PLANE, Vec(1.0,0.0,0.0));

    WorldConstraint* faceConstraintY = new WorldConstraint();
    faceConstraintY->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    faceConstraintY->setTranslationConstraint(AxisPlaneConstraint::PLANE, Vec(0.0,1.0,0.0));
    
    WorldConstraint* faceConstraintZ = new WorldConstraint();
    faceConstraintZ->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    faceConstraintZ->setTranslationConstraint(AxisPlaneConstraint::PLANE, Vec(0.0,0.0,1.0));




    QVector3D v[8]={
	QVector3D(-0.25, -0.25, -0.25),
	QVector3D(0.25, -0.25, -0.25),
	QVector3D(0.25, 0.25, -0.25),
	QVector3D(-0.25, 0.25, -0.25),
	QVector3D(-0.25, 0.25, 0.25),
	QVector3D(0.25, 0.25, 0.25),
	QVector3D(0.25, -0.25, 0.25),
	QVector3D(-0.25, -0.25, 0.25)
    };
    for(i=0; i<8; i++)
	node[i] = new functionNode(this, v[i]);

    edge[0] = new functionEdge(this, node[0], node[1]);
    edge[1] = new functionEdge(this, node[1], node[2]);
    edge[2] = new functionEdge(this, node[2], node[3]);
    edge[3] = new functionEdge(this, node[3], node[0]);
    edge[4] = new functionEdge(this, node[4], node[5]);
    edge[5] = new functionEdge(this, node[5], node[6]);
    edge[6] = new functionEdge(this, node[6], node[7]);
    edge[7] = new functionEdge(this, node[7], node[4]);
    edge[8] = new functionEdge(this, node[0], node[7]);
    edge[9] = new functionEdge(this, node[1], node[6]);
    edge[10] = new functionEdge(this, node[2], node[5]);
    edge[11] = new functionEdge(this, node[3], node[4]);

    QVector3D ve[12]={
	QVector3D(0, -0.25, -0.25),
	QVector3D(0.25, 0, -0.25),
	QVector3D(0, 0.25, -0.25),
	QVector3D(-0.25, 0, -0.25),
	QVector3D(-0.25, 0, 0.25),
	QVector3D(0, 0.25, 0.25),
	QVector3D(0.25, 0, 0.25),
	QVector3D(0, -0.25, 0.25),
	QVector3D(-0.25, -0.25, 0),
	QVector3D(0.25, -0.25, 0),
	QVector3D(0.25, 0.25, 0),
	QVector3D(-0.25, 0.25, 0)
    };

    for(i=0; i<12; i++)
    {
	edgeNode[i] = new functionNode(this, ve[i]); 
	edgeNode[i]->setColor(QColor(Qt::green));
	frame(i)->setTranslation(Vec(ve[i].x(), ve[i].y(), ve[i].z()));
	if(i==3 || i ==1 || i == 4 || i==6)
	{
	    frame(i)->setConstraint(edgeConstraintX);
	}else
	if(i==0 || i==2 || i ==5 || i==7)
	{
	    frame(i)->setConstraint(edgeConstraintY);
	}else
	if(i==8||i==9||i==10||i==11)
	{
	    frame(i)->setConstraint(edgeConstraintZ);
	}
    
    }

    QVector3D vf[6]={
	QVector3D(0, 0, -0.25),
	QVector3D(0, 0, 0.25),
	QVector3D(0, -0.25, 0),
	QVector3D(0.25, 0, 0),
	QVector3D(0, 0.25, 0),
	QVector3D(-0.25, 0, 0)
    
    };

    for(i=0; i<6; i++)
    {
	faceNode[i] = new functionNode(this, vf[i]); 
	faceNode[i]->setColor(QColor(Qt::green));
	frame(12+i)->setTranslation(Vec(vf[i].x(), vf[i].y(), vf[i].z()));
	if(i==3|| i==5)
	{
	    frame(12+i)->setConstraint(faceConstraintX);
	}else if(i==0||i==1)
	{
	    	
	    frame(12+i)->setConstraint(faceConstraintZ);
	
	}else if(i==4||i==2)
	{
	    frame(12+i)->setConstraint(faceConstraintY);
	}
    }

    middleNode = new functionNode(this, QVector3D(0, 0, 0));    
    middleNode->setColor(QColor(Qt::blue));
    frame(18)->setTranslation(Vec(0, 0, 0));

    faceEdge[0] = new functionEdge(this, faceNode[0], edgeNode[0]);
    faceEdge[1] = new functionEdge(this, faceNode[0], edgeNode[1]);
    faceEdge[2] = new functionEdge(this, faceNode[0], edgeNode[2]);
    faceEdge[3] = new functionEdge(this, faceNode[0], edgeNode[3]);
    faceEdge[4] = new functionEdge(this, faceNode[1], edgeNode[4]);
    faceEdge[5] = new functionEdge(this, faceNode[1], edgeNode[5]);
    faceEdge[6] = new functionEdge(this, faceNode[1], edgeNode[6]);
    faceEdge[7] = new functionEdge(this, faceNode[1], edgeNode[7]);
    faceEdge[8] = new functionEdge(this, faceNode[2], edgeNode[0]);
    faceEdge[9] = new functionEdge(this, faceNode[2], edgeNode[9]);
    faceEdge[10] = new functionEdge(this, faceNode[2], edgeNode[7]);
    faceEdge[11] = new functionEdge(this, faceNode[2], edgeNode[8]);
    faceEdge[12] = new functionEdge(this, faceNode[3], edgeNode[1]);
    faceEdge[13] = new functionEdge(this, faceNode[3], edgeNode[10]);
    faceEdge[14] = new functionEdge(this, faceNode[3], edgeNode[6]);
    faceEdge[15] = new functionEdge(this, faceNode[3], edgeNode[9]);
    faceEdge[16] = new functionEdge(this, faceNode[4], edgeNode[2]);
    faceEdge[17] = new functionEdge(this, faceNode[4], edgeNode[10]);
    faceEdge[18] = new functionEdge(this, faceNode[4], edgeNode[5]);
    faceEdge[19] = new functionEdge(this, faceNode[4], edgeNode[11]);
    faceEdge[20] = new functionEdge(this, faceNode[5], edgeNode[3]);
    faceEdge[21] = new functionEdge(this, faceNode[5], edgeNode[11]);
    faceEdge[22] = new functionEdge(this, faceNode[5], edgeNode[4]);
    faceEdge[23] = new functionEdge(this, faceNode[5], edgeNode[8]);

    for(i=0; i<6; i++)
    {
	innerEdge[i] = new functionEdge(this, middleNode, faceNode[i]);
    }
    selected = 19;

}

functionCube::~functionCube()
{
    int i;
    for(i=0; i<8; i++)
	delete node[i];
    for(i=0; i<12; i++)
	delete edge[i];
    for(i=0; i<12; i++)
	delete edgeNode[i];
    for(i=0; i<6; i++)
	delete faceNode[i];
    for(i=0; i<24; i++)
	delete faceEdge[i];
    delete middleNode;
    for(i=0; i<6; i++)
	delete innerEdge[i];

}

void functionCube::draw(bool names)
{
    int i;
    float px, py, pz;
    setColor(20);
    for(i=0; i<8; i++)
	node[i]->draw(0, 0, 0, 0);
    for(i=0; i<12; i++)
	edge[i]->draw();

    for(i=0; i<12; i++)
    {
	if(names)
	    glPushName(i);
	setColor(i);
	frame(i)->getTranslation(px, py, pz);
	edgeNode[i]->mat.setToIdentity();
	edgeNode[i]->mat.translate(QVector3D(px, py, pz));
	edgeNode[i]->draw(0, 0, 0, 0);
	if(names)
	    glPopName();
    }

    for(i=0; i<6; i++)
    {
	if(names)
	    glPushName(12+i);
	setColor(12+i);
	frame(12+i)->getTranslation(px, py, pz);
	faceNode[i]->mat.setToIdentity();
	faceNode[i]->mat.translate(QVector3D(px, py, pz));
	faceNode[i]->draw(0, 0, 0, 0);
	if(names)
	    glPopName();
    }

    setColor(20);
    for(i=0; i<24; i++)
	faceEdge[i]->draw();

    if(names)
	glPushName(18);
    setColor(18);
    frame(18)->getTranslation(px, py, pz);
    middleNode->mat.setToIdentity();
    middleNode->mat.translate(QVector3D(px, py, pz));
    middleNode->draw(0, 0, 0, 0);
    if(names)
	glPopName();

    setColor(20);
    for(i=0; i<6; i++)
	innerEdge[i]->draw();

}

void functionCube::setColor(unsigned short nb)
{
    if(nb==selected)
    {
	glColor3f(0.9f, 0.9f, 0.0); 
    }
    else
	glColor3f(0.9f, 0.0, 0.9f);
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
