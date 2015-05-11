//
// C++ Implementation: viewcar
//
// Description: 
//
//
// Author: Peter <marcusk@i.ua>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "viewcar.h"

ViewCar::ViewCar(QWidget *parent)
 : QGLWidget(parent)
{
	QGLFormat::setDefaultFormat(QGLFormat(QGL::SampleBuffers));
}


ViewCar::~ViewCar()
{
}


