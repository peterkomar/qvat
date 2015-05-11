//
// C++ Interface: system
//
// Description: 
//
//
// Author: Peter <marcusk@i.ua>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SYSTEM_H
#define SYSTEM_H

#include <QtGui>
#ifndef QT_NO_OPENGL
	#include <QtOpenGL>
#endif

/**
	@author Peter <marcusk@i.ua>
*/
class System{

private:
    System() {};

public:
    static QString s_openGL;
	static bool useEightBitPalette;
	static QColor buttonText;
	static int fps;
	static float animSpeed;
	static bool tansparentIcons;
	static int valueTransparent;
public:
    static void detect_system();
	static QFont buttonFont();
};

#endif
