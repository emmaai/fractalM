#include "viewer.h"
Viewer::Viewer(QWidget *parent):QGLViewer(parent)
{
    //cube = new functionCube(parent);
    cube = NULL;
    box = NULL;
}

Viewer::~Viewer()
{
    if(cube)
	delete cube;
    if(box)
	delete box;
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
  drawCornerAxis();
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
    glDisable(GL_LIGHTING);

}

void Viewer::draw()
{
    if(cube)
	cube->draw();
    if(box)
	box->draw();
}

void Viewer::drawWithNames()
{
    if(cube)
	cube->draw(true);
    if(box)
	box->draw(true);
}

void Viewer::postSelection(const QPoint &point)
{
    qDebug() << "selected position" << point;
    qDebug() << "selected item is" << selectedName();
    if(selectedName() > 20)
	return;
    if (selectedName() == -1)
    {
      // Camera will be the default frame is no object is selected.
	setManipulatedFrame( camera()->frame() );
	if(cube)
	    cube->setSelectedFrameNumber(19); // dummy value meaning camera
	if(box)
	    box->setSelectedFrameNumber(6);
    }
    else
    {
	if(cube)
	{
	    setManipulatedFrame(cube->frame(selectedName()));
	    cube->setSelectedFrameNumber(selectedName());
	}
	if(box)
	{
	    setManipulatedFrame(box->frame(selectedName()));
	    box->setSelectedFrameNumber(selectedName());

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
