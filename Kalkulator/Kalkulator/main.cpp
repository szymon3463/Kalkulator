#include <QtWidgets/QtWidgets>

#include "mainwindow.h"

#if defined (_MSC_VER)
#ifdef _DEBUG
#pragma comment(lib,"Qt5WebKitWidgetsd.lib")
#pragma comment(lib,"Qt5Networkd.lib")
#pragma comment(lib,"Qt5Widgetsd.lib")
#pragma comment(lib,"Qt5PrintSupportd.lib")
#pragma comment(lib,"Qt5Concurrentd.lib")
#pragma comment(lib,"Qt5OpenGLd.lib")
#pragma comment(lib,"Qt5Guid.lib")
#pragma comment(lib,"Qt5Cored.lib")
#pragma comment(lib,"Qt5Xmld.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"Qt5Xmld.lib")
#else
#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"Qt5Gui.lib")
#pragma comment(lib,"Qt5Core.lib")
#pragma comment(lib,"Qt5Xml.lib")

#endif
#endif

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	MainWindow window;

	window.show();

	return app.exec();
}