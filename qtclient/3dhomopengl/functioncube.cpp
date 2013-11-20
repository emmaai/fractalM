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
	QVector3D(-0.5, -0.5, -0.5),
	QVector3D(0.5, -0.5, -0.5),
	QVector3D(0.5, 0.5, -0.5),
	QVector3D(-0.5, 0.5, -0.5),
	QVector3D(-0.5, 0.5, 0.5),
	QVector3D(0.5, 0.5, 0.5),
	QVector3D(0.5, -0.5, 0.5),
	QVector3D(-0.5, -0.5, 0.5)
    };
    for(i=0; i<8; i++)
    {
	node[i] = new functionNode(this, v[i]);
	points[i] = QVector3D(v[i].x()+0.5, v[i].y()+0.5, v[i].z()+0.5);
    }

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
	QVector3D(0, -0.5, -0.5),
	QVector3D(0.5, 0, -0.5),
	QVector3D(0, 0.5, -0.5),
	QVector3D(-0.5, 0, -0.5),
	QVector3D(-0.5, 0, 0.5),
	QVector3D(0, 0.5, 0.5),
	QVector3D(0.5, 0, 0.5),
	QVector3D(0, -0.5, 0.5),
	QVector3D(-0.5, -0.5, 0),
	QVector3D(0.5, -0.5, 0),
	QVector3D(0.5, 0.5, 0),
	QVector3D(-0.5, 0.5, 0)
    };

    for(i=0; i<12; i++)
    {
	edgeNode[i] = new functionNode(this, ve[i]); 
	points[i+8] = QVector3D(ve[i].x()+0.5, ve[i].y()+0.5, ve[i].z()+0.5);
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
	QVector3D(0, 0, -0.5),
	QVector3D(0, 0, 0.5),
	QVector3D(0, -0.5, 0),
	QVector3D(0.5, 0, 0),
	QVector3D(0, 0.5, 0),
	QVector3D(-0.5, 0, 0)
    
    };

    for(i=0; i<6; i++)
    {
	faceNode[i] = new functionNode(this, vf[i]); 
	points[i+20] = QVector3D(vf[i].x()+0.5, vf[i].y()+0.5, vf[i].z()+0.5);
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
    points[26] = QVector3D(0.5, 0.5, 0.5);
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

    functionParam[0].coordinate[0].x = points[0].x(); 
    functionParam[0].coordinate[0].y = points[0].y(); 
    functionParam[0].coordinate[0].z = points[0].z(); 

    functionParam[0].coordinate[1].x = points[8].x(); 
    functionParam[0].coordinate[1].y = points[8].y(); 
    functionParam[0].coordinate[1].z = points[8].z(); 

    functionParam[0].coordinate[2].x = points[11].x(); 
    functionParam[0].coordinate[2].y = points[11].y(); 
    functionParam[0].coordinate[2].z = points[11].z(); 

    functionParam[0].coordinate[3].x = points[20].x(); 
    functionParam[0].coordinate[3].y = points[20].y(); 
    functionParam[0].coordinate[3].z = points[20].z(); 

    functionParam[0].coordinate[4].x = points[16].x(); 
    functionParam[0].coordinate[4].y = points[16].y(); 
    functionParam[0].coordinate[4].z = points[16].z(); 

    functionParam[0].coordinate[5].x = points[22].x(); 
    functionParam[0].coordinate[5].y = points[22].y(); 
    functionParam[0].coordinate[5].z = points[22].z(); 

    functionParam[0].coordinate[6].x = points[25].x(); 
    functionParam[0].coordinate[6].y = points[25].y(); 
    functionParam[0].coordinate[6].z = points[25].z(); 

    functionParam[0].coordinate[7].x = points[26].x(); 
    functionParam[0].coordinate[7].y = points[26].y(); 
    functionParam[0].coordinate[7].z = points[26].z(); 

    functionParam[1].coordinate[0].x = points[1].x(); 
    functionParam[1].coordinate[0].y = points[1].y(); 
    functionParam[1].coordinate[0].z = points[1].z(); 

    functionParam[1].coordinate[1].x = points[8].x(); 
    functionParam[1].coordinate[1].y = points[8].y(); 
    functionParam[1].coordinate[1].z = points[8].z(); 

    functionParam[1].coordinate[2].x = points[9].x(); 
    functionParam[1].coordinate[2].y = points[9].y(); 
    functionParam[1].coordinate[2].z = points[9].z(); 

    functionParam[1].coordinate[3].x = points[20].x(); 
    functionParam[1].coordinate[3].y = points[20].y(); 
    functionParam[1].coordinate[3].z = points[20].z(); 

    functionParam[1].coordinate[4].x = points[17].x(); 
    functionParam[1].coordinate[4].y = points[17].y(); 
    functionParam[1].coordinate[4].z = points[17].z(); 

    functionParam[1].coordinate[5].x = points[22].x(); 
    functionParam[1].coordinate[5].y = points[22].y(); 
    functionParam[1].coordinate[5].z = points[22].z(); 

    functionParam[1].coordinate[6].x = points[23].x(); 
    functionParam[1].coordinate[6].y = points[23].y(); 
    functionParam[1].coordinate[6].z = points[23].z(); 

    functionParam[1].coordinate[7].x = points[26].x(); 
    functionParam[1].coordinate[7].y = points[26].y(); 
    functionParam[1].coordinate[7].z = points[26].z(); 

    functionParam[2].coordinate[0].x = points[3].x(); 
    functionParam[2].coordinate[0].y = points[3].y(); 
    functionParam[2].coordinate[0].z = points[3].z(); 

    functionParam[2].coordinate[1].x = points[10].x(); 
    functionParam[2].coordinate[1].y = points[10].y(); 
    functionParam[2].coordinate[1].z = points[10].z(); 

    functionParam[2].coordinate[2].x = points[11].x(); 
    functionParam[2].coordinate[2].y = points[11].y(); 
    functionParam[2].coordinate[2].z = points[11].z(); 

    functionParam[2].coordinate[3].x = points[20].x(); 
    functionParam[2].coordinate[3].y = points[20].y(); 
    functionParam[2].coordinate[3].z = points[20].z(); 

    functionParam[2].coordinate[4].x = points[19].x(); 
    functionParam[2].coordinate[4].y = points[19].y(); 
    functionParam[2].coordinate[4].z = points[19].z(); 

    functionParam[2].coordinate[5].x = points[24].x(); 
    functionParam[2].coordinate[5].y = points[24].y(); 
    functionParam[2].coordinate[5].z = points[24].z(); 

    functionParam[2].coordinate[6].x = points[25].x(); 
    functionParam[2].coordinate[6].y = points[25].y(); 
    functionParam[2].coordinate[6].z = points[25].z(); 

    functionParam[2].coordinate[7].x = points[26].x(); 
    functionParam[2].coordinate[7].y = points[26].y(); 
    functionParam[2].coordinate[7].z = points[26].z(); 

    functionParam[3].coordinate[0].x = points[2].x(); 
    functionParam[3].coordinate[0].y = points[2].y(); 
    functionParam[3].coordinate[0].z = points[2].z(); 

    functionParam[3].coordinate[1].x = points[10].x(); 
    functionParam[3].coordinate[1].y = points[10].y(); 
    functionParam[3].coordinate[1].z = points[10].z(); 
    
    functionParam[3].coordinate[2].x = points[9].x(); 
    functionParam[3].coordinate[2].y = points[9].y(); 
    functionParam[3].coordinate[2].z = points[9].z(); 

    functionParam[3].coordinate[3].x = points[20].x(); 
    functionParam[3].coordinate[3].y = points[20].y(); 
    functionParam[3].coordinate[3].z = points[20].z(); 

    functionParam[3].coordinate[4].x = points[18].x(); 
    functionParam[3].coordinate[4].y = points[18].y(); 
    functionParam[3].coordinate[4].z = points[18].z(); 

    functionParam[3].coordinate[5].x = points[24].x(); 
    functionParam[3].coordinate[5].y = points[24].y(); 
    functionParam[3].coordinate[5].z = points[24].z(); 

    functionParam[3].coordinate[6].x = points[23].x(); 
    functionParam[3].coordinate[6].y = points[23].y(); 
    functionParam[3].coordinate[6].z = points[23].z(); 

    functionParam[3].coordinate[7].x = points[26].x(); 
    functionParam[3].coordinate[7].y = points[26].y(); 
    functionParam[3].coordinate[7].z = points[26].z(); 

    functionParam[4].coordinate[0].x = points[7].x(); 
    functionParam[4].coordinate[0].y = points[7].y(); 
    functionParam[4].coordinate[0].z = points[7].z(); 

    functionParam[4].coordinate[1].x = points[15].x(); 
    functionParam[4].coordinate[1].y = points[15].y(); 
    functionParam[4].coordinate[1].z = points[15].z(); 

    functionParam[4].coordinate[2].x = points[12].x(); 
    functionParam[4].coordinate[2].y = points[12].y(); 
    functionParam[4].coordinate[2].z = points[12].z(); 

    functionParam[4].coordinate[3].x = points[21].x(); 
    functionParam[4].coordinate[3].y = points[21].y(); 
    functionParam[4].coordinate[3].z = points[21].z(); 

    functionParam[4].coordinate[4].x = points[16].x(); 
    functionParam[4].coordinate[4].y = points[16].y(); 
    functionParam[4].coordinate[4].z = points[16].z(); 

    functionParam[4].coordinate[5].x = points[22].x(); 
    functionParam[4].coordinate[5].y = points[22].y(); 
    functionParam[4].coordinate[5].z = points[22].z(); 

    functionParam[4].coordinate[6].x = points[25].x(); 
    functionParam[4].coordinate[6].y = points[25].y(); 
    functionParam[4].coordinate[6].z = points[25].z(); 

    functionParam[4].coordinate[7].x = points[26].x(); 
    functionParam[4].coordinate[7].y = points[26].y(); 
    functionParam[4].coordinate[7].z = points[26].z(); 

    functionParam[5].coordinate[0].x = points[6].x(); 
    functionParam[5].coordinate[0].y = points[6].y(); 
    functionParam[5].coordinate[0].z = points[6].z(); 

    functionParam[5].coordinate[1].x = points[15].x(); 
    functionParam[5].coordinate[1].y = points[15].y(); 
    functionParam[5].coordinate[1].z = points[15].z(); 

    functionParam[5].coordinate[2].x = points[14].x(); 
    functionParam[5].coordinate[2].y = points[14].y(); 
    functionParam[5].coordinate[2].z = points[14].z(); 

    functionParam[5].coordinate[3].x = points[21].x(); 
    functionParam[5].coordinate[3].y = points[21].y(); 
    functionParam[5].coordinate[3].z = points[21].z(); 

    functionParam[5].coordinate[4].x = points[17].x(); 
    functionParam[5].coordinate[4].y = points[17].y(); 
    functionParam[5].coordinate[4].z = points[17].z(); 

    functionParam[5].coordinate[5].x = points[22].x(); 
    functionParam[5].coordinate[5].y = points[22].y(); 
    functionParam[5].coordinate[5].z = points[22].z(); 

    functionParam[5].coordinate[6].x = points[23].x(); 
    functionParam[5].coordinate[6].y = points[23].y(); 
    functionParam[5].coordinate[6].z = points[23].z(); 

    functionParam[5].coordinate[7].x = points[26].x(); 
    functionParam[5].coordinate[7].y = points[26].y(); 
    functionParam[5].coordinate[7].z = points[26].z(); 

    functionParam[6].coordinate[0].x = points[4].x(); 
    functionParam[6].coordinate[0].y = points[4].y(); 
    functionParam[6].coordinate[0].z = points[4].z(); 

    functionParam[6].coordinate[1].x = points[13].x(); 
    functionParam[6].coordinate[1].y = points[13].y(); 
    functionParam[6].coordinate[1].z = points[13].z(); 

    functionParam[6].coordinate[2].x = points[12].x(); 
    functionParam[6].coordinate[2].y = points[12].y(); 
    functionParam[6].coordinate[2].z = points[12].z(); 

    functionParam[6].coordinate[3].x = points[21].x(); 
    functionParam[6].coordinate[3].y = points[21].y(); 
    functionParam[6].coordinate[3].z = points[21].z(); 

    functionParam[6].coordinate[4].x = points[19].x(); 
    functionParam[6].coordinate[4].y = points[19].y(); 
    functionParam[6].coordinate[4].z = points[19].z(); 

    functionParam[6].coordinate[5].x = points[24].x(); 
    functionParam[6].coordinate[5].y = points[24].y(); 
    functionParam[6].coordinate[5].z = points[24].z(); 

    functionParam[6].coordinate[6].x = points[25].x(); 
    functionParam[6].coordinate[6].y = points[25].y(); 
    functionParam[6].coordinate[6].z = points[25].z(); 

    functionParam[6].coordinate[7].x = points[26].x(); 
    functionParam[6].coordinate[7].y = points[26].y(); 
    functionParam[6].coordinate[7].z = points[26].z(); 

    functionParam[7].coordinate[0].x = points[5].x(); 
    functionParam[7].coordinate[0].y = points[5].y(); 
    functionParam[7].coordinate[0].z = points[5].z(); 

    functionParam[7].coordinate[1].x = points[13].x(); 
    functionParam[7].coordinate[1].y = points[13].y(); 
    functionParam[7].coordinate[1].z = points[13].z(); 
    
    functionParam[7].coordinate[2].x = points[14].x(); 
    functionParam[7].coordinate[2].y = points[14].y(); 
    functionParam[7].coordinate[2].z = points[14].z(); 

    functionParam[7].coordinate[3].x = points[21].x(); 
    functionParam[7].coordinate[3].y = points[21].y(); 
    functionParam[7].coordinate[3].z = points[21].z(); 

    functionParam[7].coordinate[4].x = points[18].x(); 
    functionParam[7].coordinate[4].y = points[18].y(); 
    functionParam[7].coordinate[4].z = points[18].z(); 

    functionParam[7].coordinate[5].x = points[24].x(); 
    functionParam[7].coordinate[5].y = points[24].y(); 
    functionParam[7].coordinate[5].z = points[24].z(); 

    functionParam[7].coordinate[6].x = points[23].x(); 
    functionParam[7].coordinate[6].y = points[23].y(); 
    functionParam[7].coordinate[6].z = points[23].z(); 

    functionParam[7].coordinate[7].x = points[26].x(); 
    functionParam[7].coordinate[7].y = points[26].y(); 
    functionParam[7].coordinate[7].z = points[26].z(); 

    for(i=0; i< PARANUMBER; i++)
	functionParam[i].funcNo = 0;


    selected = 19;
    samePoint = 0;

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
	if(px < -0.5) 
	    px = -0.5+0.0001;
	else if(px > 0.5)
	    px = 0.5 -0.0001;

	if(py < -0.5) 
	    py = -0.5+0.0001;
	else if(py > 0.5)
	    py = 0.5 -0.0001;

	if(pz < -0.5) 
	    pz = -0.5+0.0001;
	else if(pz > 0.5)
	    pz = 0.5 -0.0001;
	if(points[i+8]!= QVector3D(px+0.5, py+0.5, pz+0.5))
	{
	    points[i+8] = QVector3D(px+0.5, py+0.5, pz+0.5);
	    samePoint |= (1<<(i+8));
	}else
	    samePoint &= ~(1<<(i+8));
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
	if(px < -0.5) 
	    px = -0.5+0.0001;
	else if(px > 0.5)
	    px = 0.5 -0.0001;

	if(py < -0.5) 
	    py = -0.5+0.0001;
	else if(py > 0.5)
	    py = 0.5 -0.0001;

	if(pz < -0.5) 
	    pz = -0.5+0.0001;
	else if(pz > 0.5)
	    pz = 0.5 -0.0001;

	if(points[i+20]!= QVector3D(px+0.5, py+0.5, pz+0.5))
	{
	    points[i+20] = QVector3D(px+0.5, py+0.5, pz+0.5);
	    samePoint |= (1<<(i+20));
	}else
	    samePoint &= ~(1<<(i+20));
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

    if(px < -0.5) 
	px = -0.5+0.0001;
    else if(px > 0.5)
	px = 0.5 -0.0001;

    if(py < -0.5) 
	py = -0.5+0.0001;
    else if(py > 0.5)
	py = 0.5 -0.0001;

    if(pz < -0.5) 
	pz = -0.5+0.0001;
    else if(pz > 0.5)
	pz = 0.5 -0.0001;

    if(points[26]!= QVector3D(px+0.5, py+0.5, pz+0.5))
    {
	points[26] = QVector3D(px+0.5, py+0.5, pz+0.5);
	samePoint |= (1<<26);
    }else
	samePoint &= ~(1<<26);

    middleNode->mat.setToIdentity();
    middleNode->mat.translate(QVector3D(px, py, pz));
    middleNode->draw(0, 0, 0, 0);
    if(names)
	glPopName();

    setColor(20);
    for(i=0; i<6; i++)
	innerEdge[i]->draw();
    if(samePoint)
    {

	functionParam[0].coordinate[0].x = points[0].x(); 
	functionParam[0].coordinate[0].y = points[0].y(); 
	functionParam[0].coordinate[0].z = points[0].z(); 

	functionParam[0].coordinate[1].x = points[8].x(); 
	functionParam[0].coordinate[1].y = points[8].y(); 
	functionParam[0].coordinate[1].z = points[8].z(); 

	functionParam[0].coordinate[2].x = points[11].x(); 
	functionParam[0].coordinate[2].y = points[11].y(); 
	functionParam[0].coordinate[2].z = points[11].z(); 

	functionParam[0].coordinate[3].x = points[20].x(); 
	functionParam[0].coordinate[3].y = points[20].y(); 
	functionParam[0].coordinate[3].z = points[20].z(); 

	functionParam[0].coordinate[4].x = points[16].x(); 
	functionParam[0].coordinate[4].y = points[16].y(); 
	functionParam[0].coordinate[4].z = points[16].z(); 

	functionParam[0].coordinate[5].x = points[22].x(); 
	functionParam[0].coordinate[5].y = points[22].y(); 
	functionParam[0].coordinate[5].z = points[22].z(); 

	functionParam[0].coordinate[6].x = points[25].x(); 
	functionParam[0].coordinate[6].y = points[25].y(); 
	functionParam[0].coordinate[6].z = points[25].z(); 

	functionParam[0].coordinate[7].x = points[26].x(); 
	functionParam[0].coordinate[7].y = points[26].y(); 
	functionParam[0].coordinate[7].z = points[26].z(); 

	functionParam[1].coordinate[0].x = points[1].x(); 
	functionParam[1].coordinate[0].y = points[1].y(); 
	functionParam[1].coordinate[0].z = points[1].z(); 

	functionParam[1].coordinate[1].x = points[8].x(); 
	functionParam[1].coordinate[1].y = points[8].y(); 
	functionParam[1].coordinate[1].z = points[8].z(); 

	functionParam[1].coordinate[2].x = points[9].x(); 
	functionParam[1].coordinate[2].y = points[9].y(); 
	functionParam[1].coordinate[2].z = points[9].z(); 

	functionParam[1].coordinate[3].x = points[20].x(); 
	functionParam[1].coordinate[3].y = points[20].y(); 
	functionParam[1].coordinate[3].z = points[20].z(); 

	functionParam[1].coordinate[4].x = points[17].x(); 
	functionParam[1].coordinate[4].y = points[17].y(); 
	functionParam[1].coordinate[4].z = points[17].z(); 

	functionParam[1].coordinate[5].x = points[22].x(); 
	functionParam[1].coordinate[5].y = points[22].y(); 
	functionParam[1].coordinate[5].z = points[22].z(); 

	functionParam[1].coordinate[6].x = points[23].x(); 
	functionParam[1].coordinate[6].y = points[23].y(); 
	functionParam[1].coordinate[6].z = points[23].z(); 

	functionParam[1].coordinate[7].x = points[26].x(); 
	functionParam[1].coordinate[7].y = points[26].y(); 
	functionParam[1].coordinate[7].z = points[26].z(); 

	functionParam[2].coordinate[0].x = points[3].x(); 
	functionParam[2].coordinate[0].y = points[3].y(); 
	functionParam[2].coordinate[0].z = points[3].z(); 

	functionParam[2].coordinate[1].x = points[10].x(); 
	functionParam[2].coordinate[1].y = points[10].y(); 
	functionParam[2].coordinate[1].z = points[10].z(); 

	functionParam[2].coordinate[2].x = points[11].x(); 
	functionParam[2].coordinate[2].y = points[11].y(); 
	functionParam[2].coordinate[2].z = points[11].z(); 

	functionParam[2].coordinate[3].x = points[20].x(); 
	functionParam[2].coordinate[3].y = points[20].y(); 
	functionParam[2].coordinate[3].z = points[20].z(); 

	functionParam[2].coordinate[4].x = points[19].x(); 
	functionParam[2].coordinate[4].y = points[19].y(); 
	functionParam[2].coordinate[4].z = points[19].z(); 

	functionParam[2].coordinate[5].x = points[24].x(); 
	functionParam[2].coordinate[5].y = points[24].y(); 
	functionParam[2].coordinate[5].z = points[24].z(); 

	functionParam[2].coordinate[6].x = points[25].x(); 
	functionParam[2].coordinate[6].y = points[25].y(); 
	functionParam[2].coordinate[6].z = points[25].z(); 

	functionParam[2].coordinate[7].x = points[26].x(); 
	functionParam[2].coordinate[7].y = points[26].y(); 
	functionParam[2].coordinate[7].z = points[26].z(); 

	functionParam[3].coordinate[0].x = points[2].x(); 
	functionParam[3].coordinate[0].y = points[2].y(); 
	functionParam[3].coordinate[0].z = points[2].z(); 

	functionParam[3].coordinate[1].x = points[10].x(); 
	functionParam[3].coordinate[1].y = points[10].y(); 
	functionParam[3].coordinate[1].z = points[10].z(); 
	
	functionParam[3].coordinate[2].x = points[9].x(); 
	functionParam[3].coordinate[2].y = points[9].y(); 
	functionParam[3].coordinate[2].z = points[9].z(); 

	functionParam[3].coordinate[3].x = points[20].x(); 
	functionParam[3].coordinate[3].y = points[20].y(); 
	functionParam[3].coordinate[3].z = points[20].z(); 

	functionParam[3].coordinate[4].x = points[18].x(); 
	functionParam[3].coordinate[4].y = points[18].y(); 
	functionParam[3].coordinate[4].z = points[18].z(); 

	functionParam[3].coordinate[5].x = points[24].x(); 
	functionParam[3].coordinate[5].y = points[24].y(); 
	functionParam[3].coordinate[5].z = points[24].z(); 

	functionParam[3].coordinate[6].x = points[23].x(); 
	functionParam[3].coordinate[6].y = points[23].y(); 
	functionParam[3].coordinate[6].z = points[23].z(); 

	functionParam[3].coordinate[7].x = points[26].x(); 
	functionParam[3].coordinate[7].y = points[26].y(); 
	functionParam[3].coordinate[7].z = points[26].z(); 

	functionParam[4].coordinate[0].x = points[7].x(); 
	functionParam[4].coordinate[0].y = points[7].y(); 
	functionParam[4].coordinate[0].z = points[7].z(); 

	functionParam[4].coordinate[1].x = points[15].x(); 
	functionParam[4].coordinate[1].y = points[15].y(); 
	functionParam[4].coordinate[1].z = points[15].z(); 

	functionParam[4].coordinate[2].x = points[12].x(); 
	functionParam[4].coordinate[2].y = points[12].y(); 
	functionParam[4].coordinate[2].z = points[12].z(); 

	functionParam[4].coordinate[3].x = points[21].x(); 
	functionParam[4].coordinate[3].y = points[21].y(); 
	functionParam[4].coordinate[3].z = points[21].z(); 

	functionParam[4].coordinate[4].x = points[16].x(); 
	functionParam[4].coordinate[4].y = points[16].y(); 
	functionParam[4].coordinate[4].z = points[16].z(); 

	functionParam[4].coordinate[5].x = points[22].x(); 
	functionParam[4].coordinate[5].y = points[22].y(); 
	functionParam[4].coordinate[5].z = points[22].z(); 

	functionParam[4].coordinate[6].x = points[25].x(); 
	functionParam[4].coordinate[6].y = points[25].y(); 
	functionParam[4].coordinate[6].z = points[25].z(); 

	functionParam[4].coordinate[7].x = points[26].x(); 
	functionParam[4].coordinate[7].y = points[26].y(); 
	functionParam[4].coordinate[7].z = points[26].z(); 

	functionParam[5].coordinate[0].x = points[6].x(); 
	functionParam[5].coordinate[0].y = points[6].y(); 
	functionParam[5].coordinate[0].z = points[6].z(); 

	functionParam[5].coordinate[1].x = points[15].x(); 
	functionParam[5].coordinate[1].y = points[15].y(); 
	functionParam[5].coordinate[1].z = points[15].z(); 

	functionParam[5].coordinate[2].x = points[14].x(); 
	functionParam[5].coordinate[2].y = points[14].y(); 
	functionParam[5].coordinate[2].z = points[14].z(); 

	functionParam[5].coordinate[3].x = points[21].x(); 
	functionParam[5].coordinate[3].y = points[21].y(); 
	functionParam[5].coordinate[3].z = points[21].z(); 

	functionParam[5].coordinate[4].x = points[17].x(); 
	functionParam[5].coordinate[4].y = points[17].y(); 
	functionParam[5].coordinate[4].z = points[17].z(); 

	functionParam[5].coordinate[5].x = points[22].x(); 
	functionParam[5].coordinate[5].y = points[22].y(); 
	functionParam[5].coordinate[5].z = points[22].z(); 

	functionParam[5].coordinate[6].x = points[23].x(); 
	functionParam[5].coordinate[6].y = points[23].y(); 
	functionParam[5].coordinate[6].z = points[23].z(); 

	functionParam[5].coordinate[7].x = points[26].x(); 
	functionParam[5].coordinate[7].y = points[26].y(); 
	functionParam[5].coordinate[7].z = points[26].z(); 

	functionParam[6].coordinate[0].x = points[4].x(); 
	functionParam[6].coordinate[0].y = points[4].y(); 
	functionParam[6].coordinate[0].z = points[4].z(); 

	functionParam[6].coordinate[1].x = points[13].x(); 
	functionParam[6].coordinate[1].y = points[13].y(); 
	functionParam[6].coordinate[1].z = points[13].z(); 

	functionParam[6].coordinate[2].x = points[12].x(); 
	functionParam[6].coordinate[2].y = points[12].y(); 
	functionParam[6].coordinate[2].z = points[12].z(); 

	functionParam[6].coordinate[3].x = points[21].x(); 
	functionParam[6].coordinate[3].y = points[21].y(); 
	functionParam[6].coordinate[3].z = points[21].z(); 

	functionParam[6].coordinate[4].x = points[19].x(); 
	functionParam[6].coordinate[4].y = points[19].y(); 
	functionParam[6].coordinate[4].z = points[19].z(); 

	functionParam[6].coordinate[5].x = points[24].x(); 
	functionParam[6].coordinate[5].y = points[24].y(); 
	functionParam[6].coordinate[5].z = points[24].z(); 

	functionParam[6].coordinate[6].x = points[25].x(); 
	functionParam[6].coordinate[6].y = points[25].y(); 
	functionParam[6].coordinate[6].z = points[25].z(); 

	functionParam[6].coordinate[7].x = points[26].x(); 
	functionParam[6].coordinate[7].y = points[26].y(); 
	functionParam[6].coordinate[7].z = points[26].z(); 

	functionParam[7].coordinate[0].x = points[5].x(); 
	functionParam[7].coordinate[0].y = points[5].y(); 
	functionParam[7].coordinate[0].z = points[5].z(); 

	functionParam[7].coordinate[1].x = points[13].x(); 
	functionParam[7].coordinate[1].y = points[13].y(); 
	functionParam[7].coordinate[1].z = points[13].z(); 
	
	functionParam[7].coordinate[2].x = points[14].x(); 
	functionParam[7].coordinate[2].y = points[14].y(); 
	functionParam[7].coordinate[2].z = points[14].z(); 

	functionParam[7].coordinate[3].x = points[21].x(); 
	functionParam[7].coordinate[3].y = points[21].y(); 
	functionParam[7].coordinate[3].z = points[21].z(); 

	functionParam[7].coordinate[4].x = points[18].x(); 
	functionParam[7].coordinate[4].y = points[18].y(); 
	functionParam[7].coordinate[4].z = points[18].z(); 

	functionParam[7].coordinate[5].x = points[24].x(); 
	functionParam[7].coordinate[5].y = points[24].y(); 
	functionParam[7].coordinate[5].z = points[24].z(); 

	functionParam[7].coordinate[6].x = points[23].x(); 
	functionParam[7].coordinate[6].y = points[23].y(); 
	functionParam[7].coordinate[6].z = points[23].z(); 

	functionParam[7].coordinate[7].x = points[26].x(); 
	functionParam[7].coordinate[7].y = points[26].y(); 
	functionParam[7].coordinate[7].z = points[26].z(); 
	
	emit writeParam((char *)functionParam);
    }//if(samePoint)

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

functionTH::functionTH(QObject *parent):QObject(parent)
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




    QVector3D v[4]={
	QVector3D(-0.5, -1/sqrt(12.0), 0),
	QVector3D(0.5, -1/sqrt(12.0), 0),
	QVector3D(0, sqrt(3.0)/2.0-1.0/sqrt(12.0), 0),
	QVector3D(0, 0, sqrt(2.0)/sqrt(3.0)),
    };
    for(i=0; i<4; i++)
    {
	node[i] = new functionNode(this, v[i]);
	points[i] = QVector3D(v[i].x()+0.5, v[i].y()+0.5, v[i].z()+0.5);
    }

    edge[0] = new functionEdge(this, node[0], node[1]);
    edge[1] = new functionEdge(this, node[1], node[2]);
    edge[2] = new functionEdge(this, node[2], node[0]);
    edge[3] = new functionEdge(this, node[0], node[3]);
    edge[4] = new functionEdge(this, node[1], node[3]);
    edge[5] = new functionEdge(this, node[2], node[3]);

    QVector3D ve[6]={
	QVector3D(0, -1/sqrt(12.0), 0),
	QVector3D(-0.5*0.5, 0.5*0.5/sqrt(3.0), 0),
	QVector3D(0.5*0.5, 0.5*0.5/sqrt(3.0), 0),
	QVector3D(-0.5*0.5, -1/sqrt(12.0)*0.5, sqrt(2.0/3.0)*0.5),
	QVector3D(0.5*0.5, -1/sqrt(12.0)*0.5, sqrt(2.0/3.0)*0.5),
	QVector3D(0, (sqrt(3.0)/2.0-1.0/sqrt(12.0))*0.5, sqrt(2.0/3.0)*0.5),
    };

    for(i=0; i<6; i++)
    {
	edgeNode[i] = new functionNode(this, ve[i]); 
	points[i+4] = QVector3D(ve[i].x()+0.5, ve[i].y()+0.5, ve[i].z()+0.5);
	frame(i)->setTranslation(Vec(ve[i].x(), ve[i].y(), ve[i].z()));
    }

    faceEdge[0] = new functionEdge(this, edgeNode[0], edgeNode[1]);
    faceEdge[1] = new functionEdge(this, edgeNode[1], edgeNode[2]);
    faceEdge[2] = new functionEdge(this, edgeNode[2], edgeNode[0]);
    faceEdge[3] = new functionEdge(this, edgeNode[3], edgeNode[4]);
    faceEdge[4] = new functionEdge(this, edgeNode[4], edgeNode[5]);
    faceEdge[5] = new functionEdge(this, edgeNode[5], edgeNode[3]);
    faceEdge[6] = new functionEdge(this, edgeNode[0], edgeNode[3]);
    faceEdge[7] = new functionEdge(this, edgeNode[0], edgeNode[4]);
    faceEdge[8] = new functionEdge(this, edgeNode[1], edgeNode[3]);
    faceEdge[9] = new functionEdge(this, edgeNode[1], edgeNode[5]);
    faceEdge[10] = new functionEdge(this, edgeNode[2], edgeNode[4]);
    faceEdge[11] = new functionEdge(this, edgeNode[2], edgeNode[5]);

    
    middleNode = new functionNode(this, QVector3D(0, 0, 1/sqrt(6.0)*0.5));    
    points[10] = QVector3D(0.5, 0.5, 0.5);
    frame(6)->setTranslation(Vec(0, 0, 1/sqrt(6.0)*0.5));

    for(i=0; i<6; i++)
    {
	innerEdge[i] = new functionEdge(this, middleNode, edgeNode[i]);
    }

    functionParam[0].coordinate[0].x = points[0].x(); 
    functionParam[0].coordinate[0].y = points[0].y(); 
    functionParam[0].coordinate[0].z = points[0].z(); 

    functionParam[0].coordinate[1].x = points[8].x(); 
    functionParam[0].coordinate[1].y = points[8].y(); 
    functionParam[0].coordinate[1].z = points[8].z(); 

    functionParam[0].coordinate[2].x = points[11].x(); 
    functionParam[0].coordinate[2].y = points[11].y(); 
    functionParam[0].coordinate[2].z = points[11].z(); 

    functionParam[0].coordinate[3].x = points[20].x(); 
    functionParam[0].coordinate[3].y = points[20].y(); 
    functionParam[0].coordinate[3].z = points[20].z(); 

    functionParam[0].coordinate[4].x = points[16].x(); 
    functionParam[0].coordinate[4].y = points[16].y(); 
    functionParam[0].coordinate[4].z = points[16].z(); 

    functionParam[0].coordinate[5].x = points[22].x(); 
    functionParam[0].coordinate[5].y = points[22].y(); 
    functionParam[0].coordinate[5].z = points[22].z(); 

    functionParam[0].coordinate[6].x = points[25].x(); 
    functionParam[0].coordinate[6].y = points[25].y(); 
    functionParam[0].coordinate[6].z = points[25].z(); 

    functionParam[0].coordinate[7].x = points[26].x(); 
    functionParam[0].coordinate[7].y = points[26].y(); 
    functionParam[0].coordinate[7].z = points[26].z(); 

    functionParam[1].coordinate[0].x = points[1].x(); 
    functionParam[1].coordinate[0].y = points[1].y(); 
    functionParam[1].coordinate[0].z = points[1].z(); 

    functionParam[1].coordinate[1].x = points[8].x(); 
    functionParam[1].coordinate[1].y = points[8].y(); 
    functionParam[1].coordinate[1].z = points[8].z(); 

    functionParam[1].coordinate[2].x = points[9].x(); 
    functionParam[1].coordinate[2].y = points[9].y(); 
    functionParam[1].coordinate[2].z = points[9].z(); 

    functionParam[1].coordinate[3].x = points[20].x(); 
    functionParam[1].coordinate[3].y = points[20].y(); 
    functionParam[1].coordinate[3].z = points[20].z(); 

    functionParam[1].coordinate[4].x = points[17].x(); 
    functionParam[1].coordinate[4].y = points[17].y(); 
    functionParam[1].coordinate[4].z = points[17].z(); 

    functionParam[1].coordinate[5].x = points[22].x(); 
    functionParam[1].coordinate[5].y = points[22].y(); 
    functionParam[1].coordinate[5].z = points[22].z(); 

    functionParam[1].coordinate[6].x = points[23].x(); 
    functionParam[1].coordinate[6].y = points[23].y(); 
    functionParam[1].coordinate[6].z = points[23].z(); 

    functionParam[1].coordinate[7].x = points[26].x(); 
    functionParam[1].coordinate[7].y = points[26].y(); 
    functionParam[1].coordinate[7].z = points[26].z(); 

    functionParam[2].coordinate[0].x = points[3].x(); 
    functionParam[2].coordinate[0].y = points[3].y(); 
    functionParam[2].coordinate[0].z = points[3].z(); 

    functionParam[2].coordinate[1].x = points[10].x(); 
    functionParam[2].coordinate[1].y = points[10].y(); 
    functionParam[2].coordinate[1].z = points[10].z(); 

    functionParam[2].coordinate[2].x = points[11].x(); 
    functionParam[2].coordinate[2].y = points[11].y(); 
    functionParam[2].coordinate[2].z = points[11].z(); 

    functionParam[2].coordinate[3].x = points[20].x(); 
    functionParam[2].coordinate[3].y = points[20].y(); 
    functionParam[2].coordinate[3].z = points[20].z(); 

    functionParam[2].coordinate[4].x = points[19].x(); 
    functionParam[2].coordinate[4].y = points[19].y(); 
    functionParam[2].coordinate[4].z = points[19].z(); 

    functionParam[2].coordinate[5].x = points[24].x(); 
    functionParam[2].coordinate[5].y = points[24].y(); 
    functionParam[2].coordinate[5].z = points[24].z(); 

    functionParam[2].coordinate[6].x = points[25].x(); 
    functionParam[2].coordinate[6].y = points[25].y(); 
    functionParam[2].coordinate[6].z = points[25].z(); 

    functionParam[2].coordinate[7].x = points[26].x(); 
    functionParam[2].coordinate[7].y = points[26].y(); 
    functionParam[2].coordinate[7].z = points[26].z(); 

    functionParam[3].coordinate[0].x = points[2].x(); 
    functionParam[3].coordinate[0].y = points[2].y(); 
    functionParam[3].coordinate[0].z = points[2].z(); 

    functionParam[3].coordinate[1].x = points[10].x(); 
    functionParam[3].coordinate[1].y = points[10].y(); 
    functionParam[3].coordinate[1].z = points[10].z(); 
    
    functionParam[3].coordinate[2].x = points[9].x(); 
    functionParam[3].coordinate[2].y = points[9].y(); 
    functionParam[3].coordinate[2].z = points[9].z(); 

    functionParam[3].coordinate[3].x = points[20].x(); 
    functionParam[3].coordinate[3].y = points[20].y(); 
    functionParam[3].coordinate[3].z = points[20].z(); 

    functionParam[3].coordinate[4].x = points[18].x(); 
    functionParam[3].coordinate[4].y = points[18].y(); 
    functionParam[3].coordinate[4].z = points[18].z(); 

    functionParam[3].coordinate[5].x = points[24].x(); 
    functionParam[3].coordinate[5].y = points[24].y(); 
    functionParam[3].coordinate[5].z = points[24].z(); 

    functionParam[3].coordinate[6].x = points[23].x(); 
    functionParam[3].coordinate[6].y = points[23].y(); 
    functionParam[3].coordinate[6].z = points[23].z(); 

    functionParam[3].coordinate[7].x = points[26].x(); 
    functionParam[3].coordinate[7].y = points[26].y(); 
    functionParam[3].coordinate[7].z = points[26].z(); 

    functionParam[4].coordinate[0].x = points[7].x(); 
    functionParam[4].coordinate[0].y = points[7].y(); 
    functionParam[4].coordinate[0].z = points[7].z(); 

    functionParam[4].coordinate[1].x = points[15].x(); 
    functionParam[4].coordinate[1].y = points[15].y(); 
    functionParam[4].coordinate[1].z = points[15].z(); 

    functionParam[4].coordinate[2].x = points[12].x(); 
    functionParam[4].coordinate[2].y = points[12].y(); 
    functionParam[4].coordinate[2].z = points[12].z(); 

    functionParam[4].coordinate[3].x = points[21].x(); 
    functionParam[4].coordinate[3].y = points[21].y(); 
    functionParam[4].coordinate[3].z = points[21].z(); 

    functionParam[4].coordinate[4].x = points[16].x(); 
    functionParam[4].coordinate[4].y = points[16].y(); 
    functionParam[4].coordinate[4].z = points[16].z(); 

    functionParam[4].coordinate[5].x = points[22].x(); 
    functionParam[4].coordinate[5].y = points[22].y(); 
    functionParam[4].coordinate[5].z = points[22].z(); 

    functionParam[4].coordinate[6].x = points[25].x(); 
    functionParam[4].coordinate[6].y = points[25].y(); 
    functionParam[4].coordinate[6].z = points[25].z(); 

    functionParam[4].coordinate[7].x = points[26].x(); 
    functionParam[4].coordinate[7].y = points[26].y(); 
    functionParam[4].coordinate[7].z = points[26].z(); 

    functionParam[5].coordinate[0].x = points[6].x(); 
    functionParam[5].coordinate[0].y = points[6].y(); 
    functionParam[5].coordinate[0].z = points[6].z(); 

    functionParam[5].coordinate[1].x = points[15].x(); 
    functionParam[5].coordinate[1].y = points[15].y(); 
    functionParam[5].coordinate[1].z = points[15].z(); 

    functionParam[5].coordinate[2].x = points[14].x(); 
    functionParam[5].coordinate[2].y = points[14].y(); 
    functionParam[5].coordinate[2].z = points[14].z(); 

    functionParam[5].coordinate[3].x = points[21].x(); 
    functionParam[5].coordinate[3].y = points[21].y(); 
    functionParam[5].coordinate[3].z = points[21].z(); 

    functionParam[5].coordinate[4].x = points[17].x(); 
    functionParam[5].coordinate[4].y = points[17].y(); 
    functionParam[5].coordinate[4].z = points[17].z(); 

    functionParam[5].coordinate[5].x = points[22].x(); 
    functionParam[5].coordinate[5].y = points[22].y(); 
    functionParam[5].coordinate[5].z = points[22].z(); 

    functionParam[5].coordinate[6].x = points[23].x(); 
    functionParam[5].coordinate[6].y = points[23].y(); 
    functionParam[5].coordinate[6].z = points[23].z(); 

    functionParam[5].coordinate[7].x = points[26].x(); 
    functionParam[5].coordinate[7].y = points[26].y(); 
    functionParam[5].coordinate[7].z = points[26].z(); 

    functionParam[6].coordinate[0].x = points[4].x(); 
    functionParam[6].coordinate[0].y = points[4].y(); 
    functionParam[6].coordinate[0].z = points[4].z(); 

    functionParam[6].coordinate[1].x = points[13].x(); 
    functionParam[6].coordinate[1].y = points[13].y(); 
    functionParam[6].coordinate[1].z = points[13].z(); 

    functionParam[6].coordinate[2].x = points[12].x(); 
    functionParam[6].coordinate[2].y = points[12].y(); 
    functionParam[6].coordinate[2].z = points[12].z(); 

    functionParam[6].coordinate[3].x = points[21].x(); 
    functionParam[6].coordinate[3].y = points[21].y(); 
    functionParam[6].coordinate[3].z = points[21].z(); 

    functionParam[6].coordinate[4].x = points[19].x(); 
    functionParam[6].coordinate[4].y = points[19].y(); 
    functionParam[6].coordinate[4].z = points[19].z(); 

    functionParam[6].coordinate[5].x = points[24].x(); 
    functionParam[6].coordinate[5].y = points[24].y(); 
    functionParam[6].coordinate[5].z = points[24].z(); 

    functionParam[6].coordinate[6].x = points[25].x(); 
    functionParam[6].coordinate[6].y = points[25].y(); 
    functionParam[6].coordinate[6].z = points[25].z(); 

    functionParam[6].coordinate[7].x = points[26].x(); 
    functionParam[6].coordinate[7].y = points[26].y(); 
    functionParam[6].coordinate[7].z = points[26].z(); 

    functionParam[7].coordinate[0].x = points[5].x(); 
    functionParam[7].coordinate[0].y = points[5].y(); 
    functionParam[7].coordinate[0].z = points[5].z(); 

    functionParam[7].coordinate[1].x = points[13].x(); 
    functionParam[7].coordinate[1].y = points[13].y(); 
    functionParam[7].coordinate[1].z = points[13].z(); 
    
    functionParam[7].coordinate[2].x = points[14].x(); 
    functionParam[7].coordinate[2].y = points[14].y(); 
    functionParam[7].coordinate[2].z = points[14].z(); 

    functionParam[7].coordinate[3].x = points[21].x(); 
    functionParam[7].coordinate[3].y = points[21].y(); 
    functionParam[7].coordinate[3].z = points[21].z(); 

    functionParam[7].coordinate[4].x = points[18].x(); 
    functionParam[7].coordinate[4].y = points[18].y(); 
    functionParam[7].coordinate[4].z = points[18].z(); 

    functionParam[7].coordinate[5].x = points[24].x(); 
    functionParam[7].coordinate[5].y = points[24].y(); 
    functionParam[7].coordinate[5].z = points[24].z(); 

    functionParam[7].coordinate[6].x = points[23].x(); 
    functionParam[7].coordinate[6].y = points[23].y(); 
    functionParam[7].coordinate[6].z = points[23].z(); 

    functionParam[7].coordinate[7].x = points[26].x(); 
    functionParam[7].coordinate[7].y = points[26].y(); 
    functionParam[7].coordinate[7].z = points[26].z(); 

    for(i=0; i< PARANUMBER; i++)
	functionParam[i].funcNo = 0;


    selected = 19;
    samePoint = 0;

}

functionTH::~functionTH()
{
    int i;
    for(i=0; i<4; i++)
	delete node[i];
    for(i=0; i<4; i++)
	delete edge[i];
    for(i=0; i<6; i++)
	delete edgeNode[i];
    for(i=0; i<12; i++)
	delete faceEdge[i];
    delete middleNode;
    for(i=0; i<6; i++)
	delete innerEdge[i];

}

void functionTH::draw(bool names)
{
    int i;
    float px, py, pz;
    setColor(20);
    for(i=0; i<4; i++)
	node[i]->draw(0, 0, 0, 0);
    for(i=0; i<6; i++)
	edge[i]->draw();

    for(i=0; i<6; i++)
    {
	if(names)
	    glPushName(i);
	setColor(i);
	frame(i)->getTranslation(px, py, pz);
	switch(i){
	    case 0:
		if(px < -0.5) 
		    px = -0.5+0.0001;
		else if(px > 0.5)
		    px = 0.5 -0.0001;
		py = -1/sqrt(12.0);
		pz = 0;
		break;
	    case 1:
		if(px < -0.5) 
		    px = -0.5+0.0001;
		else if(px > 0)
		    px = -0.0001; 
		py = (0.5+px)*sqrt(3.0)-1/sqrt(12.0);
		pz = 0;
		break;
	    case 2:
		if(px > 0.5) 
		    px = 0.5-0.0001;
		else if(px < 0)
		    px = 0.0001; 
		py = (0.5-px)*sqrt(3.0)-1/sqrt(12.0);
		pz = 0;
		break;
	    case 3:
		if(px < -0.5) 
		    px = -0.5+0.0001;
		else if(px > 0)
		    px = -0.0001; 
		py = (0.5+px)/sqrt(3.0)-1/sqrt(12.0);
		pz= (0.5+px)*2*sqrt(2.0)/sqrt(3.0);
		break;
	    case 4:
		if(px > 0.5) 
		    px = 0.5-0.0001;
		else if(px < 0)
		    px = 0.0001; 
		py = (0.5-px)/sqrt(3.0)-1/sqrt(12.0);
		pz= (0.5-px)*2*sqrt(2.0)/sqrt(3.0);
		break;
	    case 5:
		px = 0;
		if(py > 1/sqrt(3.0))
		    py = 1/sqrt(3.0)-0.0001;
		if(py < 0)
		    py = 0.0001;
		pz = sqrt(2.0)*(1/sqrt(3.0)-py);
		break;
	    default:
		break;
	
	}
	if(points[i+4]!= QVector3D(px+0.5, py+0.5, pz+0.5))
	{
	    points[i+4] = QVector3D(px+0.5, py+0.5, pz+0.5);
	    samePoint |= (1<<(i+4));
	}else
	    samePoint &= ~(1<<(i+4));
	edgeNode[i]->mat.setToIdentity();
	edgeNode[i]->mat.translate(QVector3D(px, py, pz));
	edgeNode[i]->draw(0, 0, 0, 0);
	frame(i)->setTranslation(Vec(px, py, pz));
	if(names)
	    glPopName();
    }

    setColor(20);
    for(i=0; i<12; i++)
	faceEdge[i]->draw();

    if(names)
	glPushName(6);
    setColor(6);
    frame(6)->getTranslation(px, py, pz);

    if(pz < 0)
	pz = 0.0001;
    else if(pz > sqrt(2.0/3.0))
	pz = sqrt(2.0/3.0);

    if(px < -(1.0-pz/sqrt(2.0/3.0))/2) 
	px = -(1.0-pz/sqrt(2.0/3.0))/2+0.0001;
    else if(px >(1.0-pz/sqrt(2.0/3.0))/2 )
	px = (1.0-pz/sqrt(2.0/3.0))/2-0.0001;

    if(py < pz/2.0/sqrt(2.0)-1.0/sqrt(12.0))
	py = pz/2.0/sqrt(2.0)-1.0/sqrt(12.0)+0.0001;

    else if(py > sqrt(3.0)*((1.0-pz/sqrt(2.0/3.0))/2-fabs(px))+pz/2.0/sqrt(2.0)-1.0/sqrt(12.0))
	py = sqrt(3.0)*((1.0-pz/sqrt(2.0/3.0))/2-fabs(px))+pz/2.0/sqrt(2.0)-1.0/sqrt(12.0)-0.0001;


    if(points[10]!= QVector3D(px+0.5, py+0.5, pz+0.5))
    {
	points[10] = QVector3D(px+0.5, py+0.5, pz+0.5);
	samePoint |= (1<<10);
    }else
	samePoint &= ~(1<<10);

    middleNode->mat.setToIdentity();
    middleNode->mat.translate(QVector3D(px, py, pz));
    middleNode->draw(0, 0, 0, 0);
    frame(6)->setTranslation(Vec(px, py, pz));
    if(names)
	glPopName();

    setColor(20);
    for(i=0; i<6; i++)
	innerEdge[i]->draw();

    if(samePoint)
    {

	functionParam[0].coordinate[0].x = points[0].x(); 
	functionParam[0].coordinate[0].y = points[0].y(); 
	functionParam[0].coordinate[0].z = points[0].z(); 

	functionParam[0].coordinate[1].x = points[8].x(); 
	functionParam[0].coordinate[1].y = points[8].y(); 
	functionParam[0].coordinate[1].z = points[8].z(); 

	functionParam[0].coordinate[2].x = points[11].x(); 
	functionParam[0].coordinate[2].y = points[11].y(); 
	functionParam[0].coordinate[2].z = points[11].z(); 

	functionParam[0].coordinate[3].x = points[20].x(); 
	functionParam[0].coordinate[3].y = points[20].y(); 
	functionParam[0].coordinate[3].z = points[20].z(); 

	functionParam[0].coordinate[4].x = points[16].x(); 
	functionParam[0].coordinate[4].y = points[16].y(); 
	functionParam[0].coordinate[4].z = points[16].z(); 

	functionParam[0].coordinate[5].x = points[22].x(); 
	functionParam[0].coordinate[5].y = points[22].y(); 
	functionParam[0].coordinate[5].z = points[22].z(); 

	functionParam[0].coordinate[6].x = points[25].x(); 
	functionParam[0].coordinate[6].y = points[25].y(); 
	functionParam[0].coordinate[6].z = points[25].z(); 

	functionParam[0].coordinate[7].x = points[26].x(); 
	functionParam[0].coordinate[7].y = points[26].y(); 
	functionParam[0].coordinate[7].z = points[26].z(); 

	functionParam[1].coordinate[0].x = points[1].x(); 
	functionParam[1].coordinate[0].y = points[1].y(); 
	functionParam[1].coordinate[0].z = points[1].z(); 

	functionParam[1].coordinate[1].x = points[8].x(); 
	functionParam[1].coordinate[1].y = points[8].y(); 
	functionParam[1].coordinate[1].z = points[8].z(); 

	functionParam[1].coordinate[2].x = points[9].x(); 
	functionParam[1].coordinate[2].y = points[9].y(); 
	functionParam[1].coordinate[2].z = points[9].z(); 

	functionParam[1].coordinate[3].x = points[20].x(); 
	functionParam[1].coordinate[3].y = points[20].y(); 
	functionParam[1].coordinate[3].z = points[20].z(); 

	functionParam[1].coordinate[4].x = points[17].x(); 
	functionParam[1].coordinate[4].y = points[17].y(); 
	functionParam[1].coordinate[4].z = points[17].z(); 

	functionParam[1].coordinate[5].x = points[22].x(); 
	functionParam[1].coordinate[5].y = points[22].y(); 
	functionParam[1].coordinate[5].z = points[22].z(); 

	functionParam[1].coordinate[6].x = points[23].x(); 
	functionParam[1].coordinate[6].y = points[23].y(); 
	functionParam[1].coordinate[6].z = points[23].z(); 

	functionParam[1].coordinate[7].x = points[26].x(); 
	functionParam[1].coordinate[7].y = points[26].y(); 
	functionParam[1].coordinate[7].z = points[26].z(); 

	functionParam[2].coordinate[0].x = points[3].x(); 
	functionParam[2].coordinate[0].y = points[3].y(); 
	functionParam[2].coordinate[0].z = points[3].z(); 

	functionParam[2].coordinate[1].x = points[10].x(); 
	functionParam[2].coordinate[1].y = points[10].y(); 
	functionParam[2].coordinate[1].z = points[10].z(); 

	functionParam[2].coordinate[2].x = points[11].x(); 
	functionParam[2].coordinate[2].y = points[11].y(); 
	functionParam[2].coordinate[2].z = points[11].z(); 

	functionParam[2].coordinate[3].x = points[20].x(); 
	functionParam[2].coordinate[3].y = points[20].y(); 
	functionParam[2].coordinate[3].z = points[20].z(); 

	functionParam[2].coordinate[4].x = points[19].x(); 
	functionParam[2].coordinate[4].y = points[19].y(); 
	functionParam[2].coordinate[4].z = points[19].z(); 

	functionParam[2].coordinate[5].x = points[24].x(); 
	functionParam[2].coordinate[5].y = points[24].y(); 
	functionParam[2].coordinate[5].z = points[24].z(); 

	functionParam[2].coordinate[6].x = points[25].x(); 
	functionParam[2].coordinate[6].y = points[25].y(); 
	functionParam[2].coordinate[6].z = points[25].z(); 

	functionParam[2].coordinate[7].x = points[26].x(); 
	functionParam[2].coordinate[7].y = points[26].y(); 
	functionParam[2].coordinate[7].z = points[26].z(); 

	functionParam[3].coordinate[0].x = points[2].x(); 
	functionParam[3].coordinate[0].y = points[2].y(); 
	functionParam[3].coordinate[0].z = points[2].z(); 

	functionParam[3].coordinate[1].x = points[10].x(); 
	functionParam[3].coordinate[1].y = points[10].y(); 
	functionParam[3].coordinate[1].z = points[10].z(); 
	
	functionParam[3].coordinate[2].x = points[9].x(); 
	functionParam[3].coordinate[2].y = points[9].y(); 
	functionParam[3].coordinate[2].z = points[9].z(); 

	functionParam[3].coordinate[3].x = points[20].x(); 
	functionParam[3].coordinate[3].y = points[20].y(); 
	functionParam[3].coordinate[3].z = points[20].z(); 

	functionParam[3].coordinate[4].x = points[18].x(); 
	functionParam[3].coordinate[4].y = points[18].y(); 
	functionParam[3].coordinate[4].z = points[18].z(); 

	functionParam[3].coordinate[5].x = points[24].x(); 
	functionParam[3].coordinate[5].y = points[24].y(); 
	functionParam[3].coordinate[5].z = points[24].z(); 

	functionParam[3].coordinate[6].x = points[23].x(); 
	functionParam[3].coordinate[6].y = points[23].y(); 
	functionParam[3].coordinate[6].z = points[23].z(); 

	functionParam[3].coordinate[7].x = points[26].x(); 
	functionParam[3].coordinate[7].y = points[26].y(); 
	functionParam[3].coordinate[7].z = points[26].z(); 

	functionParam[4].coordinate[0].x = points[7].x(); 
	functionParam[4].coordinate[0].y = points[7].y(); 
	functionParam[4].coordinate[0].z = points[7].z(); 

	functionParam[4].coordinate[1].x = points[15].x(); 
	functionParam[4].coordinate[1].y = points[15].y(); 
	functionParam[4].coordinate[1].z = points[15].z(); 

	functionParam[4].coordinate[2].x = points[12].x(); 
	functionParam[4].coordinate[2].y = points[12].y(); 
	functionParam[4].coordinate[2].z = points[12].z(); 

	functionParam[4].coordinate[3].x = points[21].x(); 
	functionParam[4].coordinate[3].y = points[21].y(); 
	functionParam[4].coordinate[3].z = points[21].z(); 

	functionParam[4].coordinate[4].x = points[16].x(); 
	functionParam[4].coordinate[4].y = points[16].y(); 
	functionParam[4].coordinate[4].z = points[16].z(); 

	functionParam[4].coordinate[5].x = points[22].x(); 
	functionParam[4].coordinate[5].y = points[22].y(); 
	functionParam[4].coordinate[5].z = points[22].z(); 

	functionParam[4].coordinate[6].x = points[25].x(); 
	functionParam[4].coordinate[6].y = points[25].y(); 
	functionParam[4].coordinate[6].z = points[25].z(); 

	functionParam[4].coordinate[7].x = points[26].x(); 
	functionParam[4].coordinate[7].y = points[26].y(); 
	functionParam[4].coordinate[7].z = points[26].z(); 

	functionParam[5].coordinate[0].x = points[6].x(); 
	functionParam[5].coordinate[0].y = points[6].y(); 
	functionParam[5].coordinate[0].z = points[6].z(); 

	functionParam[5].coordinate[1].x = points[15].x(); 
	functionParam[5].coordinate[1].y = points[15].y(); 
	functionParam[5].coordinate[1].z = points[15].z(); 

	functionParam[5].coordinate[2].x = points[14].x(); 
	functionParam[5].coordinate[2].y = points[14].y(); 
	functionParam[5].coordinate[2].z = points[14].z(); 

	functionParam[5].coordinate[3].x = points[21].x(); 
	functionParam[5].coordinate[3].y = points[21].y(); 
	functionParam[5].coordinate[3].z = points[21].z(); 

	functionParam[5].coordinate[4].x = points[17].x(); 
	functionParam[5].coordinate[4].y = points[17].y(); 
	functionParam[5].coordinate[4].z = points[17].z(); 

	functionParam[5].coordinate[5].x = points[22].x(); 
	functionParam[5].coordinate[5].y = points[22].y(); 
	functionParam[5].coordinate[5].z = points[22].z(); 

	functionParam[5].coordinate[6].x = points[23].x(); 
	functionParam[5].coordinate[6].y = points[23].y(); 
	functionParam[5].coordinate[6].z = points[23].z(); 

	functionParam[5].coordinate[7].x = points[26].x(); 
	functionParam[5].coordinate[7].y = points[26].y(); 
	functionParam[5].coordinate[7].z = points[26].z(); 

	functionParam[6].coordinate[0].x = points[4].x(); 
	functionParam[6].coordinate[0].y = points[4].y(); 
	functionParam[6].coordinate[0].z = points[4].z(); 

	functionParam[6].coordinate[1].x = points[13].x(); 
	functionParam[6].coordinate[1].y = points[13].y(); 
	functionParam[6].coordinate[1].z = points[13].z(); 

	functionParam[6].coordinate[2].x = points[12].x(); 
	functionParam[6].coordinate[2].y = points[12].y(); 
	functionParam[6].coordinate[2].z = points[12].z(); 

	functionParam[6].coordinate[3].x = points[21].x(); 
	functionParam[6].coordinate[3].y = points[21].y(); 
	functionParam[6].coordinate[3].z = points[21].z(); 

	functionParam[6].coordinate[4].x = points[19].x(); 
	functionParam[6].coordinate[4].y = points[19].y(); 
	functionParam[6].coordinate[4].z = points[19].z(); 

	functionParam[6].coordinate[5].x = points[24].x(); 
	functionParam[6].coordinate[5].y = points[24].y(); 
	functionParam[6].coordinate[5].z = points[24].z(); 

	functionParam[6].coordinate[6].x = points[25].x(); 
	functionParam[6].coordinate[6].y = points[25].y(); 
	functionParam[6].coordinate[6].z = points[25].z(); 

	functionParam[6].coordinate[7].x = points[26].x(); 
	functionParam[6].coordinate[7].y = points[26].y(); 
	functionParam[6].coordinate[7].z = points[26].z(); 

	functionParam[7].coordinate[0].x = points[5].x(); 
	functionParam[7].coordinate[0].y = points[5].y(); 
	functionParam[7].coordinate[0].z = points[5].z(); 

	functionParam[7].coordinate[1].x = points[13].x(); 
	functionParam[7].coordinate[1].y = points[13].y(); 
	functionParam[7].coordinate[1].z = points[13].z(); 
	
	functionParam[7].coordinate[2].x = points[14].x(); 
	functionParam[7].coordinate[2].y = points[14].y(); 
	functionParam[7].coordinate[2].z = points[14].z(); 

	functionParam[7].coordinate[3].x = points[21].x(); 
	functionParam[7].coordinate[3].y = points[21].y(); 
	functionParam[7].coordinate[3].z = points[21].z(); 

	functionParam[7].coordinate[4].x = points[18].x(); 
	functionParam[7].coordinate[4].y = points[18].y(); 
	functionParam[7].coordinate[4].z = points[18].z(); 

	functionParam[7].coordinate[5].x = points[24].x(); 
	functionParam[7].coordinate[5].y = points[24].y(); 
	functionParam[7].coordinate[5].z = points[24].z(); 

	functionParam[7].coordinate[6].x = points[23].x(); 
	functionParam[7].coordinate[6].y = points[23].y(); 
	functionParam[7].coordinate[6].z = points[23].z(); 

	functionParam[7].coordinate[7].x = points[26].x(); 
	functionParam[7].coordinate[7].y = points[26].y(); 
	functionParam[7].coordinate[7].z = points[26].z(); 
	
	emit writeParam((char *)functionParam);
    }//if(samePoint)

}

void functionTH::setColor(unsigned short nb)
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

    glLineWidth(1);
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
