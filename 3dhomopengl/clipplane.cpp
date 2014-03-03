#include "clipplane.h"
using namespace qglviewer;
clipBox::clipBox(QObject *parent):QObject(parent)
{
    int i;
    for(i=0; i<6; i++)
    {
	frame_[i] = new ManipulatedFrame();
    }
    selected = 6;

    width=length=height=0;
    //set position of each plane
    WorldConstraint* ConstraintX = new WorldConstraint();
    ConstraintX->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    ConstraintX->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(1.0,0.0,0.0));
    frame(0)->setConstraint(ConstraintX);
    frame(1)->setConstraint(ConstraintX);

    WorldConstraint* ConstraintY = new WorldConstraint();
    ConstraintY->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    ConstraintY->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(0.0,1.0,0.0));
    frame(2)->setConstraint(ConstraintY);
    frame(3)->setConstraint(ConstraintY);

    WorldConstraint* ConstraintZ = new WorldConstraint();
    ConstraintZ->setRotationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
    ConstraintZ->setTranslationConstraint(AxisPlaneConstraint::AXIS, Vec(0.0,0.0,1.0));
    frame(4)->setConstraint(ConstraintZ);
    frame(5)->setConstraint(ConstraintZ);

}

clipBox::~clipBox()
{

}

void clipBox::initBox(float x, float y, float z)
{
    width = x;
    length = y;
    height = z;
    frame(0)->setTranslation(Vec(-0.5*width, 0.0, 0.0));
    frame(1)->setTranslation(Vec(0.5*width, 0.0, 0.0));
    frame(2)->setTranslation(Vec(0.0, -0.5*length, 0.0));
    frame(3)->setTranslation(Vec(0.0, 0.5*length, 0.0));
    frame(4)->setTranslation(Vec(0.0, 0.0, -0.5*height));
    frame(5)->setTranslation(Vec(0.0, 0.0, 0.5*height));
    
}

void clipBox::enablePlane()
{
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);
    glEnable(GL_CLIP_PLANE4);
    glEnable(GL_CLIP_PLANE5);

}

void clipBox::draw(bool names)
{
    float vex[6][3];
    int i=0;
    static const GLdouble equationZ1[] = { 0.0, 0.0, 1.0, 0.0 };
    static const GLdouble equationZ2[] = { 0.0, 0.0, -1.0, 0.0 };
    static const GLdouble equationX1[] = { 1.0, 0.0, 0.0, 0.0 };
    static const GLdouble equationX2[] = { -1.0, 0.0, 0.0, 0.0 };
    static const GLdouble equationY1[] = { 0.0, 1.0, 0.0, 0.0 };
    static const GLdouble equationY2[] = { 0.0, -1.0, 0.0, 0.0 };

  const float nbSteps = 200.0;
    glBegin(GL_QUAD_STRIP);
  for (int i=0; i<nbSteps; ++i)
    {
      const float ratio = i/nbSteps;
      const float angle = 21.0*ratio;
      const float c = cos(angle);
      const float s = sin(angle);
      const float r1 = 1.0 - 0.8f*ratio;
      const float r2 = 0.8f - 0.8f*ratio;
      const float alt = ratio - 0.5f;
      const float nor = 0.5f;
      const float up = sqrt(1.0-nor*nor);
      glColor3f(1.0-ratio, 0.2f , ratio);
      glNormal3f(nor*c, up, nor*s);
      glVertex3f(r1*c, alt, r1*s);
      glVertex3f(r2*c, alt+0.05f, r2*s);
    }
  glEnd();

    for(i=0; i<6;i++)
	frame(i)->getPosition(vex[i][0], vex[i][1], vex[i][2]);

    glPushMatrix();
    if(names)
	glPushName(0);
	glMultMatrixd(frame(0)->matrix());
	glClipPlane(GL_CLIP_PLANE0, equationX1);
	setColor(0, 0);
	drawPlane(Vec(0.001, 0.0, 0.0),0, height, length);
	setColor(0, 1);
	drawLine(Vec(0.001, vex[2][1]+0.001, vex[4][2]+0.001),
	    Vec(0.001, vex[3][1]-0.001, vex[4][2]+0.001), 
	    Vec(0.001, vex[3][1]-0.001, vex[5][2]-0.001),
	    Vec(0.001, vex[2][1]+0.001, vex[5][2]-0.001));
    if(names)
	glPopName();
    glPopMatrix();

    glPushMatrix();
    if(names)
	glPushName(1);
	glMultMatrixd(frame(1)->matrix());
	glClipPlane(GL_CLIP_PLANE1, equationX2);
	setColor(1, 0);
	drawPlane(Vec(-0.001, 0.0, 0.0),0, length, height);
	setColor(1, 1);
	drawLine(Vec(-0.001, vex[2][1]+0.001, vex[4][2]+0.001),
	    Vec(-0.001, vex[3][1]-0.001, vex[4][2]+0.001), 
	    Vec(-0.001, vex[3][1]-0.001, vex[5][2]-0.001),
	    Vec(-0.001, vex[2][1]+0.001, vex[5][2]-0.001));

    if(names)
	glPopName();
    glPopMatrix();

    glPushMatrix();
    if(names)
	glPushName(2);
	glMultMatrixd(frame(2)->matrix());
	glClipPlane(GL_CLIP_PLANE2, equationY1);
	setColor(2, 0);
	drawPlane(Vec(0.0, 0.001, 0.0), 1, width, height);
	setColor(2, 1);
	drawLine(Vec(vex[0][0]+0.001, 0.001, vex[4][2]+0.001),
	    Vec(vex[1][0]-0.001, 0.001, vex[4][2]+0.001), 
	    Vec(vex[1][0], 0.001, vex[5][2]-0.001),
	    Vec(vex[0][0], 0.001, vex[5][2]-0.001));

    if(names)
	glPopName();
    glPopMatrix();

    glPushMatrix();
    if(names)
	glPushName(3);
	glMultMatrixd(frame(3)->matrix());
	glClipPlane(GL_CLIP_PLANE3, equationY2);
	setColor(3, 0);
	drawPlane(Vec(0.0, -0.001, 0.0), 1, width, height);
	setColor(3, 1);
	drawLine(Vec(vex[0][0]+0.001, -0.001, vex[4][2]+0.001),
	    Vec(vex[1][0]-0.001, -0.001, vex[4][2]+0.001), 
	    Vec(vex[1][0], -0.001, vex[5][2]-0.001),
	    Vec(vex[0][0], -0.001, vex[5][2]-0.001));
    if(names)
	glPopName();
    glPopMatrix();

    glPushMatrix();
    if(names)
	glPushName(4);
	glMultMatrixd(frame(4)->matrix());
	glClipPlane(GL_CLIP_PLANE4, equationZ1);
	setColor(4, 0);
	drawPlane(Vec(0.0, 0.0, 0.001), 2, width, length);
	setColor(4, 1);
	drawLine(Vec(vex[0][0]+0.001, vex[2][1]+0.001, 0.001),
	    Vec(vex[1][0]-0.001, vex[2][1]+0.001, 0.001), 
	    Vec(vex[1][0]-0.001, vex[3][1]-0.001, 0.001),
	    Vec(vex[0][0]+0.001, vex[3][1]-0.001, 0.001));

    if(names)
	glPopName();
    glPopMatrix();

    glPushMatrix();
    if(names)
	glPushName(5);
	glMultMatrixd(frame(5)->matrix());
	glClipPlane(GL_CLIP_PLANE5, equationZ2);
	setColor(5, 0);
	drawPlane(Vec(0.0, 0.0, -0.001), 2, width, length);
	setColor(5, 1);
	drawLine(Vec(vex[0][0]+0.001, vex[2][1]+0.001, -0.001),
	    Vec(vex[1][0]-0.001, vex[2][1]+0.001, -0.001), 
	    Vec(vex[1][0]-0.001, vex[3][1]-0.001, -0.001),
	    Vec(vex[0][0]+0.001, vex[3][1]-0.001, -0.001));

    if(names)
	glPopName();
    glPopMatrix();

}

void clipBox::setColor(unsigned short nb, float transparency)
{
    if(nb==selected)
    {
	glColor4f(0.9f, 0.9f, 0.0, transparency); 
    }
    else
	glColor4f(0.9f, 0.0, 0.9f, transparency);
}

void clipBox::drawPlane(Vec position, int direction, float width, float length)
{
    Vec c0, c1, c2, c3;
    switch(direction)
    {
	case 0: // yz plane
	    c0 = position + Vec(0.0, -0.5*length, -0.5*width);
	    c1 = position + Vec(0.0, -0.5*length, 0.5*width);
	    c2 = position + Vec(0.0, 0.5*length, 0.5*width);
	    c3 = position + Vec(0.0, 0.5*length, -0.5*width);
	    break;
	case 1: //xz plane
	    c0 = position + Vec(-0.5*length, 0.0, -0.5*width);
	    c1 = position + Vec(-0.5*length,0.0,  0.5*width);
	    c2 = position + Vec(0.5*length, 0.0, 0.5*width);
	    c3 = position + Vec(0.5*length, 0.0,  -0.5*width);
	    break;
	case 2: //xy plane
	    c0 = position + Vec(-0.5*length, -0.5*width, 0.0 );
	    c1 = position + Vec(-0.5*length, 0.5*width, 0.0);
	    c2 = position + Vec(0.5*length, 0.5*width, 0.0);
	    c3 = position + Vec(0.5*length, -0.5*width, 0.0);
	    break;
	default:
	    break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boxTexture());
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    glBegin(GL_QUADS); 
    glTexCoord2f(0, 0);              glVertex3fv(c0);
    glTexCoord2f(0, length);        glVertex3fv(c1);
    glTexCoord2f(width, length);  glVertex3fv(c2);
    glTexCoord2f(width, 0);        glVertex3fv(c3);
    glEnd();
    glPolygonOffset(0.0, 0.0);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void clipBox::drawLine(Vec c0, Vec c1, Vec c2, Vec c3)
{

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    glBegin(GL_LINE_LOOP); 
    glVertex3fv(c0);
    glVertex3fv(c1);
    glVertex3fv(c2);
    glVertex3fv(c3);
    glEnd();
    glPolygonOffset(0.0, 0.0);
    glDisable(GL_POLYGON_OFFSET_FILL);


}
GLuint clipBox::boxTexture()
{
  if (m_boxTexture)
    return m_boxTexture;

  glGenTextures( 1, &m_boxTexture );

  int texsize = 64;
  uchar *thetexture = new uchar[2*texsize*texsize];
  for (int x=0; x < texsize; x++) {
    for (int y=0; y < texsize; y++) {
      uchar alpha = 255;
      uchar lum = 255;
      if (x>5 && x<59 && y>5 && y<59)
	{
	  lum = 128;
	  alpha = 200;
	}
      int index = x*texsize + y;
      thetexture[2*index] = lum;
      thetexture[2*index+1] = alpha;
    }
  }

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_boxTexture);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA,
	       texsize, texsize, 0,
	       GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
	       thetexture);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  delete [] thetexture;

  return m_boxTexture;
}
