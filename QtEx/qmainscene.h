#ifndef QMAIN_SCENE_H
#define QMAIN_SCENE_H

#include <QtGui>

#include "private/system.h"
#include "private/itemloader.h"
#include "imageitem.h"
#include "itemtext.h"
#include "itembutton.h"

class ButtonItem;

struct MenuData
{
	QString path_pix;
	QString label;
};

typedef QList<MenuData*> MenuScene;

class QMainScene : public QGraphicsView
{
    Q_OBJECT

public:
	enum MENU_TYPE {TOP, BOTTOM};
    QMainScene(QWidget *parent = 0);
	~QMainScene();
    void start();
	
	//add items
	void addItem(qreal x, qreal y, Item* item, ItemLoader::ITEM_MOVE_FROM move_from = ItemLoader::AUTO);
	void addItem(QPointF pos, Item* item, ItemLoader::ITEM_MOVE_FROM move_from = ItemLoader::AUTO);
	
	//add menu 
	void setMenuAlpha(MENU_TYPE type=BOTTOM, int alphaBackground=123);
	void addMenu(MenuScene* menu, MENU_TYPE type=BOTTOM);
	void setBackground(QImage* imgBg);
	void setMainWidget(QWidget* widget);

    QGraphicsScene *scene;
	
protected:
    // Overidden methods:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
	void drawForeground( QPainter * painter, const QRectF & rect );
    void drawItems(QPainter *painter, int numItems, QGraphicsItem ** items, const QStyleOptionGraphicsItem* options);

private slots:
	void slot_untoggled_other(ButtonItem* );
	    
private:
    void setupWidget();
    void setupSceneItems();
    void drawBackgroundToPixmap();
    void setupScene();
	void setRenderingSystem();

    QPixmap background;
	QImage *imageBG;
    ImageItem *udlLogo;
	QWidget *mainwidget;
	int menu_count; //must be <=3, else error 1 -BOTTOM 2 - TOP 0 - no menu 3 - BOTTOM&TOP
	int alpha_top;
	int alpha_bottom;
	IMenu menu_list_bottom;
	IMenu menu_list_top;		
};

#endif // QMAIN_SCENE_H

