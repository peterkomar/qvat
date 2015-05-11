#include "qmainscene.h"
#include "private/scene.h"
#include "private/itemanimation.h"
#include "ButtonItem.h"

QMainScene::QMainScene(QWidget *parent) : QGraphicsView(parent)
{
	this->background = 0;
	this->mainwidget = 0;
	this->udlLogo = 0;
	menu_count=0;
	alpha_top=255;
	alpha_bottom=255;
	imageBG=0;	
	this->setupWidget();
    this->setupScene();
    this->setupSceneItems();
    this->drawBackgroundToPixmap();
}

QMainScene::~QMainScene()
{
    delete this->udlLogo;
	qDeleteAll(menu_list_bottom);
	qDeleteAll(menu_list_top);
}

void QMainScene::setupWidget()
{
    QRect screenRect = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    QRect windowRect(0, 0, 800, 600);
    if (screenRect.width() < 800)
        windowRect.setWidth(screenRect.width());
    if (screenRect.height() < 600)
       windowRect.setHeight(screenRect.height());
    windowRect.moveCenter(screenRect.center());
    this->setGeometry(windowRect);
    this->setMinimumSize(80, 60);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(QFrame::NoFrame);
    this->setRenderingSystem();
}

void QMainScene::setRenderingSystem()
{
   QWidget *viewport = 0;

   if(!mainwidget)
   		mainwidget = new QWidget(this);
   
   mainwidget->setAutoFillBackground(false);
   viewport = mainwidget;
   setCacheMode(QGraphicsView::CacheNone);
   setViewport(viewport);
}

void QMainScene::setMenuAlpha(MENU_TYPE type, int alphaBackground)
{
	if(type == TOP)
		alpha_top = alphaBackground;
	else
		alpha_bottom = alphaBackground;	
}

void QMainScene::setMainWidget(QWidget* widget)
{
	mainwidget = widget;
	this->setRenderingSystem();
}

void QMainScene::start()
{
    //MenuManager::instance()->itemSelected(MenuManager::ROOT, Colors::rootMenuName);
}

void QMainScene::addMenu(MenuScene* menu, MENU_TYPE type)
{
	qreal sw = scene->sceneRect().width();
	//qreal sh = scene->sceneRect().height();
	int xOffset = 15;
	//int yOffset = 10;
	int contentStartY = 0;
	int contentHeight = 510;
	
	switch(type)
	{
		case TOP: contentStartY = -478;  break;
		case BOTTOM: contentStartY = 22; break;
	}
		
		
	for(int i=0;i<menu->size();i++)
	{
		MenuData *dat = static_cast<MenuData*>(menu->at(i));
		ButtonItem *item = new ButtonItem(dat->label,ButtonItem::PANEL,  QIcon(dat->path_pix), 0);
		scene->addItem(item);
		item->setVisible(false);
		item->setZValue(10);
		item->setCheckable();
		connect(item,SIGNAL(clicked(ButtonItem*)), this, SLOT(slot_untoggled_other(ButtonItem*)));
				
		ItemAnimation *anim = new ItemAnimation(item, ItemAnimation::ANIM_IN);
		anim->setDuration(1300 * System::animSpeed);
		anim->setStartPos(QPointF(-sw, contentStartY + contentHeight - 35));
		anim->setPosAt(0.5, QPointF(-sw, contentStartY + contentHeight - 35));
		
		if(i)
		{
			ItemAnimation *a1 = (type == TOP)? menu_list_top.last(): menu_list_bottom.last(); //get width previous item
			xOffset += ((int)a1->getItem()->width())+15;
		}
		
		anim->setPosAt(0.7, QPointF(xOffset, contentStartY + contentHeight - 35));
		anim->setPosAt(1.0, QPointF(xOffset, contentStartY + contentHeight - 26));
		
		if(type == TOP)
			menu_list_top.append(anim);
		else if(type == BOTTOM)
			menu_list_bottom.append(anim);
	}
	
	if((!menu_list_top.isEmpty()) && (type == TOP) )
	   ItemLoader::instance()->init(&menu_list_top);
	
	if((!menu_list_bottom.isEmpty()) && (type == BOTTOM))
		ItemLoader::instance()->init(&menu_list_bottom);
	
	qDeleteAll(*menu);
}

void QMainScene::slot_untoggled_other(ButtonItem* item)
{
	static ButtonItem *old_item = 0;
	
	if((old_item) && (old_item != item))
		old_item->setToggled(false);
	
	old_item = item;
}

void QMainScene::setupScene()
{
	this->scene = new Scene(this);
    this->scene->setSceneRect(0, 0, 800, 600);
    setScene(this->scene);
    this->scene->setItemIndexMethod(QGraphicsScene::NoIndex);
}

void QMainScene::drawItems(QPainter *painter, int numItems, QGraphicsItem **items, const QStyleOptionGraphicsItem* options)
{
    QGraphicsView::drawItems(painter, numItems, items, options);
}

void QMainScene::setupSceneItems()
{
	this->udlLogo = new ImageItem(QImage(":/images/logotype.png"), 1000, 1000, this->scene, 0, true, 0.5f);
    this->udlLogo->setZValue(100);
}

void QMainScene::setBackground(QImage* imgBg)
{
	delete imageBG;
	
	imageBG = imgBg;
	drawBackgroundToPixmap();
}

void QMainScene::drawBackgroundToPixmap()
{
    const QRectF r = this->scene->sceneRect();
    this->background = QPixmap(qRound(r.width()), qRound(r.height()));
    this->background.fill(Qt::black);
    QPainter painter(&this->background);

	if(!imageBG)
		imageBG = new QImage(":/images/demobg.png");
	
	painter.drawImage(0, 0, *imageBG);
}

void QMainScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->drawPixmap(QPoint(0, 0), this->background);
}

void QMainScene::drawForeground(QPainter * painter, const QRectF & rect)
{
	double m_hue = 0.0;
	double m_sat(0.0);
	double m_val(0.2);
	
    // draw header/footer
	QColor hColor = QColor::fromHsvF(m_hue, m_sat, m_val);
	
	if(menu_count != 0)
	{
		if((menu_count == 3) || (menu_count == 1))
		{
			hColor.setAlpha(alpha_bottom);
			//painter->fillRect(0, 0, rect.width(), 50, hColor);
			painter->fillRect(0, rect.height() - 100, rect.width(), 100, hColor);
		}
		if(menu_count == 2)
		{
			hColor.setAlpha(alpha_top);
			painter->fillRect(0, 0, rect.width(), 50, hColor);
			//painter->fillRect(0, rect.height() - 100, rect.width(), 100, hColor);
		}
	}
}

void QMainScene::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    QGraphicsView::showEvent(event);
}


void QMainScene::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
	
	this->resetMatrix();
    this->scale(event->size().width() / 800.0, event->size().height() / 600.0);
		
    QGraphicsView::resizeEvent(event);
    Item::setMatrix(this->matrix());
    
	if (this->udlLogo){
        const QRectF r = this->scene->sceneRect();
        QRectF ttb = this->udlLogo->boundingRect();
        this->udlLogo->setPos(int((r.width() - ttb.width())), 0);
        //QRectF qtb = this->qtLogo->boundingRect();
        //this->qtLogo->setPos(802 - qtb.width(), 0);
    }
}


