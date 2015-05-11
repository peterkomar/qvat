/****************************************************************************
**
** 
** **
****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QPixmap>

#include "QtEx/qmainscene.h"
#include "viewcar.h"

class MainWindow : public QMainScene
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void toggleFullscreen();
    void start();

	ViewCar *view;
};

#endif // MAIN_WINDOW_H

