#include "system.h"

QString System::s_openGL("Don't known version openGL");
bool System::useEightBitPalette = false;
int System::fps = 100;
float System::animSpeed = 1.0;

bool System::tansparentIcons = false;
int System::valueTransparent = 60;

//color
QColor System::buttonText(QColor(255, 255, 255));

QFont System::buttonFont()
{
	QFont font;
	font.setStyleStrategy(QFont::PreferAntialias);
#if defined(Q_OS_MAC)
	font.setPixelSize(11);
	font.setFamily("Silom");
#else
	font.setPixelSize(11);
	font.setFamily("Verdana");
#endif
	return font;
}

/*!
    \fn System::detect_system()
 */
void System::detect_system()
{
#ifndef QT_NO_OPENGL
	if (QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_2_0)
		s_openGL = "2.0 or higher";
	else if (QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_5)
		s_openGL = "1.5";
	else if (QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_4)
		s_openGL = "1.4";
	else if (QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_1_3)
		s_openGL = "1.3 or lower";
	
	qDebug() << "- OpenGL version:" << System::s_openGL;

#endif
}




