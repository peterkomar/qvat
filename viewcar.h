//
// C++ Interface: viewcar
//
// Description: 
//
//
// Author: Peter <marcusk@i.ua>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef VIEWCAR_H
#define VIEWCAR_H

#include <QGLWidget>

/**
	@author Peter <marcusk@i.ua>
*/
class ViewCar : public QGLWidget
{
Q_OBJECT
public:
    ViewCar(QWidget *parent = 0);

    ~ViewCar();

};

#endif
