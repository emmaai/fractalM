#include "viewer.h"
Viewer::Viewer(QWidget *parent, QGLWidget *sharewidget):QGLViewer(parent, sharewidget)
{
    //cube = new functionCube(parent);
    cube = NULL;
    box = NULL;
    Th = NULL;
    setFocusPolicy(Qt::StrongFocus);
}

Viewer::~Viewer()
{
    if(cube)
	delete cube;
    if(box)
	delete box;
    if(Th)
	delete Th;
}

void Viewer::drawCornerAxis()
{
    int viewport[4];
    int scissor[4];

    // The viewport and the scissor are changed to fit the lower left
    // corner. Original values are saved.
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetIntegerv(GL_SCISSOR_BOX, scissor);

    // Axis viewport size, in pixels
    const int size = 150;
    glViewport(0,0,size,size);
    glScissor(0,0,size,size);

    // The Z-buffer is cleared to make the axis appear over the
    // original image.
    glClear(GL_DEPTH_BUFFER_BIT);

    // Tune for best line rendering
    glDisable(GL_LIGHTING);
    glLineWidth(3.0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixd(camera()->orientation().inverse().matrix());

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    // The viewport and the scissor are restored.
    glScissor(scissor[0],scissor[1],scissor[2],scissor[3]);
    glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);
}
  
void Viewer::postDraw()
{
  QGLViewer::postDraw();
  //drawCornerAxis();
}

void Viewer::init()
{
    setManipulatedFrame(camera()->frame());
    setHandlerKeyboardModifiers(QGLViewer::CAMERA, Qt::AltModifier);
    setHandlerKeyboardModifiers(QGLViewer::FRAME, Qt::NoModifier);
    setHandlerKeyboardModifiers(QGLViewer::CAMERA, Qt::ControlModifier);
    if(box)
    {
	box->initBox(1.0, 1.0, 1.0);
	box->enablePlane();
    }
 
    glDisable(GL_CULL_FACE);
 //glDisable(GL_LIGHTING);

}

void Viewer::draw()
{
    if(cube)
	cube->draw();
    if(box)
	box->draw();
    if(Th)
	Th->draw();
}

void Viewer::drawWithNames()
{
    if(cube)
	cube->draw(true);
    if(box)
	box->draw(true);
    if(Th)
	Th->draw(true);
}

void Viewer::endSelection(const QPoint &point)
{
    glFlush();
    // Get the number of objects that were seen through the pick matrix frustum.
    // Resets GL_RENDER mode.
    GLint nbHits = glRenderMode(GL_RENDER);
    qDebug() << "select hits " << nbHits;
    if (nbHits <= 0)
    setSelectedName(-1);
    else
    {
    // Interpret results: each object created values in the selectBuffer().
    // See the glSelectBuffer() man page for details on the buffer structure.
    // The following code depends on your selectBuffer() structure.
	
	for (int i=0; i<nbHits*4; i++)
	{
		qDebug() << "selet info " << selectBuffer()[i];
	    if ((selectBuffer())[i] ==1)
	    {
		setSelectedName((selectBuffer())[i+3]);
		break;
	    }else
		setSelectedName(-1);

	}
    }


}
void Viewer::postSelection(const QPoint &point)
{
    bool found;
    qDebug() << "selected position" << point;
    qDebug() << "selected item is" << selectedName();
    qDebug() << "selected point is " << camera()->pointUnderPixel(point, found).x
	<<camera()->pointUnderPixel(point, found).y <<camera()->pointUnderPixel(point, found).z;
    if(selectedName() > 20)
	return;
    if (selectedName() < 0 )
    {
      // Camera will be the default frame is no object is selected.
	setManipulatedFrame( camera()->frame() );
	if(cube)
	    cube->setSelectedFrameNumber(19); // dummy value meaning camera
	if(box)
	    box->setSelectedFrameNumber(6);
	if(Th)
	    Th->setSelectedFrameNumber(19);
    }
    else
    {
	if(cube)
	{
	    cube->setSelectedFrameNumber(selectedName());
	    setManipulatedFrame(cube->frame(selectedName()));
	}
	if(box)
	{
	    box->setSelectedFrameNumber(selectedName());
	    setManipulatedFrame(box->frame(selectedName()));

	}
	if(Th)
	{
	    Th->setSelectedFrameNumber(selectedName());
	    setManipulatedFrame(Th->frame(selectedName()));	
	}
    
    }
}
  
QString Viewer::helpString() const
{
  QString text("<h2>C o r n e r A x i s</h2>");
  text += "A world axis representation is drawn in the lower left corner, so that one always sees how the scene is oriented.<br><br>";
  text += "The axis is drawn in <code>postDraw()</code> with appropriate ortho camera parameters. ";
  text += "<code>glViewport</code> and <code>glScissor</code> are used to restrict the drawing area.";
  return text;
}

void Viewer::focusInEvent(QEvent *event)
{
    qDebug() << "enter viewer";
    doneCurrent();
    makeCurrent();
}

void Viewer::focusOutEvent(QEvent *event)
{
    qDebug() << "leave viewer";
    doneCurrent();
}
