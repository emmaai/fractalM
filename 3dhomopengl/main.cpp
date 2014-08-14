#include "voreen/qt/voreenapplicationqt.h"
#include "tgt/qt/qtcanvas.h"
#include "mainwindow3d.h"
#include <QApplication>
using namespace voreen;

const std::string description =
    "This is a small program that demonstrates a little of what the Voreen core library can do: \n"
    "We load the standard.vws workspace, which shows a volume rendering of the nucleon dataset \n"
    "that can be rotated and zoomed using the mouse.\n\n"
    "This is the Qt-version of this sample, there are others in the simple/-folder, like a GLUT-version.";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VoreenApplicationQt vapp("3D-Homeomophism", "3D-Homeomophism", description, argc, argv,
    VoreenApplication::ApplicationFeatures(VoreenApplication::APP_ALL &~ VoreenApplication::APP_PROCESSOR_WIDGETS));

    vapp.initialize();

    MainWindow3D w;
    VoreenApplicationQt::qtApp()->setMainWindow(&w);
    w.show();
    w.setVoreenApp(&vapp);
    
    return a.exec();
}
