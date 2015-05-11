#include "mainwindow.h"
#include "QtEx/itemtext.h"
#include "QtEx/itembutton.h"

#include <QGLWidget>

MainWindow::MainWindow(QWidget *parent) : QMainScene(parent)
{
	QGLWidget *glw = new QGLWidget(QGLFormat(QGL::SampleBuffers));
	
	setMainWidget(glw);
		
	MenuData *item=0;
	
	MenuScene *menu_list = new MenuScene;
	
	item = new MenuData;
	item->label = tr("Front Bumpers");
	item->path_pix = ":/images/bumper_f.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Rear Bumpers");
	item->path_pix = ":/images/bumper_b.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Side Skirts");
	item->path_pix = ":/images/bumper_r.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Rims");
	item->path_pix = ":/images/wheel.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Spoilers");
	//item->path_pix = ":/images/bumper_b.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Hoods");
	//item->path_pix = ":/images/bumper_r.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Headlights");
	//item->path_pix = ":/images/bumper_r.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Taillights");
	//item->path_pix = ":/images/bumper_r.png";
	menu_list->append(item);
	
	item = new MenuData;
	item->label = tr("Exhaust Tips");
	//item->path_pix = ":/images/bumper_r.png";
	menu_list->append(item);
	
	
	addMenu(menu_list);
	
	
}

MainWindow::~MainWindow()
{
    //delete this->trolltechLogo;
}


void MainWindow::start()
{
    //MenuManager::instance()->itemSelected(MenuManager::ROOT, Colors::rootMenuName);
}


void MainWindow::toggleFullscreen()
{
    if (this->isFullScreen()){
       this->showNormal();
    }
    else {
       this->showFullScreen();
    }
}


