#include "private/itemanimation.h"
#include "private/system.h"
#include "itembutton.h"
#include "itemtext.h"
#include "imageitem.h"
//#include "menumanager.h"

class ButtonBackground : public Item
{
public:
    ItemButton::BUTTONTYPE type;
    bool highlighted;
    bool pressed;
    QSize logicalSize;

    ButtonBackground(ItemButton::BUTTONTYPE type, bool highlighted, bool pressed, QSize logicalSize,
        QGraphicsScene *scene, QGraphicsItem *parent) : Item(scene, parent)
    {
        this->type = type;
        this->highlighted = highlighted;
        this->pressed = pressed;
        this->logicalSize = logicalSize;
		useSharedImage(QString(__FILE__) + static_cast<int>(type) + highlighted + pressed+QString::number(logicalSize.width())+QString::number(logicalSize.height()));
    }

protected:
    QImage *createImage(const QMatrix &matrix) const
    {
        if (type == ItemButton::SIDEBAR || type == ItemButton::PANEL)
            return createRoundButtonBackground(matrix);
        else
            return createArrowBackground(matrix);
    }

    QImage *createRoundButtonBackground(const QMatrix &matrix) const
    {
        QRect scaledRect;
        scaledRect = matrix.mapRect(QRect(0, 0, this->logicalSize.width(), this->logicalSize.height()));

        QImage *image = new QImage(scaledRect.width(), scaledRect.height(), QImage::Format_ARGB32_Premultiplied);
        image->fill(QColor(0, 0, 0, 0).rgba());
        QPainter painter(image);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        if (System::useEightBitPalette){
            painter.setPen(QColor(120, 120, 120));
            if (this->pressed)
                painter.setBrush(QColor(60, 60, 60));
            else if (this->highlighted)
                painter.setBrush(QColor(100, 100, 100));
            else
                painter.setBrush(QColor(80, 80, 80));
        }
        else {
            QLinearGradient outlinebrush(0, 0, 0, scaledRect.height());
            QLinearGradient brush(0, 0, 0, scaledRect.height());

            brush.setSpread(QLinearGradient::PadSpread);
            QColor highlight(255, 255, 255, 70);
            QColor shadow(0, 0, 0, 70);
            QColor sunken(220, 220, 220, 30);
            QColor normal1(255, 255, 245, 60);
            QColor normal2(255, 255, 235, 10);

			if (this->type == ItemButton::PANEL){
                normal1 = QColor(200, 170, 160, 50);
                normal2 = QColor(50, 10, 0, 50);
            }

           if (pressed) {
               outlinebrush.setColorAt(0.0f, shadow);
               outlinebrush.setColorAt(1.0f, highlight);
               brush.setColorAt(0.0f, sunken);
               painter.setPen(Qt::NoPen);
           } else {
               outlinebrush.setColorAt(1.0f, shadow);
               outlinebrush.setColorAt(0.0f, highlight);
               brush.setColorAt(0.0f, normal1);
               if (!this->highlighted)
                   brush.setColorAt(1.0f, normal2);
               painter.setPen(QPen(outlinebrush, 1));
           }
           painter.setBrush(brush);
        }

		if (this->type == ItemButton::PANEL)
            painter.drawRect(0, 0, scaledRect.width(), scaledRect.height());
        else
            painter.drawRoundedRect(0, 0, scaledRect.width(), scaledRect.height(), 10, 90, Qt::RelativeSize);
		
	     return image;
    }

    QImage *createArrowBackground(const QMatrix &matrix) const
    {
        QRect scaledRect;
        scaledRect = matrix.mapRect(QRect(0, 0, this->logicalSize.width(), this->logicalSize.height()));

        QImage *image = new QImage(scaledRect.width(), scaledRect.height(), QImage::Format_ARGB32_Premultiplied);
        image->fill(QColor(0, 0, 0, 0).rgba());
        QPainter painter(image);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);

        if (System::useEightBitPalette){
            painter.setPen(QColor(120, 120, 120));
            if (this->pressed)
                painter.setBrush(QColor(60, 60, 60));
            else if (this->highlighted)
                painter.setBrush(QColor(100, 100, 100));
            else
                painter.setBrush(QColor(80, 80, 80));
        }
        else {
            QLinearGradient outlinebrush(0, 0, 0, scaledRect.height());
            QLinearGradient brush(0, 0, 0, scaledRect.height());

            brush.setSpread(QLinearGradient::PadSpread);
            QColor highlight(255, 255, 255, 70);
            QColor shadow(0, 0, 0, 70);
            QColor sunken(220, 220, 220, 30);
            QColor normal1 = QColor(200, 170, 160, 50);
            QColor normal2 = QColor(50, 10, 0, 50);

           if (pressed) {
               outlinebrush.setColorAt(0.0f, shadow);
               outlinebrush.setColorAt(1.0f, highlight);
               brush.setColorAt(0.0f, sunken);
               painter.setPen(Qt::NoPen);
           } else {
               outlinebrush.setColorAt(1.0f, shadow);
               outlinebrush.setColorAt(0.0f, highlight);
               brush.setColorAt(0.0f, normal1);
               if (!this->highlighted)
                   brush.setColorAt(1.0f, normal2);
               painter.setPen(QPen(outlinebrush, 1));
           }
           painter.setBrush(brush);
        }

        painter.drawRect(0, 0, scaledRect.width(), scaledRect.height());

        float xOff = scaledRect.width() / 2;
        float yOff = scaledRect.height() / 2;
        float sizex = 3.0f * matrix.m11();
        float sizey = 1.5f * matrix.m22();
        if (this->type == ItemButton::UP)
            sizey *= -1;
        QPainterPath path;
        path.moveTo(xOff, yOff + (5 * sizey));
        path.lineTo(xOff - (4 * sizex), yOff - (3 * sizey));
        path.lineTo(xOff + (4 * sizex), yOff - (3 * sizey));
        path.lineTo(xOff, yOff + (5 * sizey));
        painter.drawPath(path);

        return image;
    }

};

void ItemButton::ItemInit(BUTTONTYPE type)
{
	this->buttonType = type;
	this->bgOn = 0;
	this->bgOff = 0;
	this->bgHighlight = 0;
	this->bgDisabled = 0;
	this->state = OFF;

	this->setAcceptsHoverEvents(true);
	this->setCursor(Qt::PointingHandCursor);
}

ItemButton::ItemButton(const QString &text, QGraphicsScene *scene, QGraphicsItem *parent, BUTTONTYPE type)
	: Item(scene, parent)
{
	ItemInit(type);
    this->buttonLabel = text;
    
    // Calculate button size:
    int w = 180;
    int h = 19;
    if (type == SIDEBAR || type == PANEL)
        this->logicalSize = QSize(w, h);
    else
        this->logicalSize = QSize(int((w / 2.0f) - 5), int(h * 1.5f));
}

ItemButton::ItemButton(const QString &pathPixmap, const QString &text, QGraphicsScene *scene, QGraphicsItem *parent, BUTTONTYPE type)
	: Item(scene, parent)
{
	ItemInit(type);
	this->buttonLabel = text;
	
	if(!QFile::exists(pathPixmap))
	{
		qDebug() << "Pixmap not found";
		return;
	}
	
	buttonPixmap = new QImage(pathPixmap);
	
	if(!buttonPixmap)
	{
		qDebug() << "Pixmap not recognized";
		return;
	}
	
    
    // Calculate button size:
	int w = 100;
	int h = 70;
	
	if(type == IMAGE)
	{
		w = buttonPixmap->width();
	    h = buttonPixmap->height();
	}
	
	if(type == PANEL)
	{
		*buttonPixmap = buttonPixmap->scaled(w,h);
	}
		
	
	QFontMetrics fm(System::buttonFont());
	int ibwSize = fm.width(text);
	int ibhSize = fm.height();
		
	h += ibhSize+4;
	
	if( (ibwSize) > w )
		w = ibwSize+15;
	
	
	if (type == SIDEBAR || type == PANEL)
		this->logicalSize = QSize(w, h);
	else
		this->logicalSize = QSize(int((w / 2.0f) - 5), int(h * 1.5f));
}

ItemButton::~ItemButton()
{
	delete buttonPixmap;
	/*if(menu)
	{
		qDeleteAll(menu);
		delete menu;
	}*/
}

void ItemButton::prepare()
{
    if (!this->prepared){
        this->prepared = true;
		this->setupButton();
        this->setupButtonBg();
    }
}


QRectF ItemButton::boundingRect() const
{
    return QRectF(0, 0, this->logicalSize.width(), this->logicalSize.height());
};

void ItemButton::setupButton()
{
    if (this->buttonLabel.isEmpty())
        return;

	ItemText *textItem = new ItemText(this->buttonLabel, System::buttonFont(), System::buttonText, -1, this->scene(), this);
    textItem->setZValue(zValue() + 2);
	
	int n =0;
	n = this->logicalSize.width();
	
	QFontMetrics fm(System::buttonFont());
	int ibSize = fm.width(this->buttonLabel);
			
	double x_item = (double)n/2.0;
	double x_text = (double)ibSize/2.0;
	
	int i=0;
	if(buttonPixmap)
	{
		ImageItem *imgitem = new ImageItem(*buttonPixmap,this->logicalSize.width(),this->logicalSize.height(),
											this->scene(), this,true);
		
		imgitem->setZValue(zValue() + 2);
		double x_img = (double)buttonPixmap->width()/2.0;
		imgitem->setPos(x_item-x_img-1.0,1);
		
		i = buttonPixmap->height()+2;
	}
	
	textItem->setPos(x_item-x_text-1.0, i);
}


void ItemButton::setState(STATE state)
{
    this->state = state;
    this->bgOn->setRecursiveVisible(state == ON);
    this->bgOff->setRecursiveVisible(state == OFF);
    this->bgHighlight->setRecursiveVisible(state == HIGHLIGHT);
    this->bgDisabled->setRecursiveVisible(state == DISABLED);
    this->setCursor(state == DISABLED ? Qt::ArrowCursor : Qt::PointingHandCursor);

}

void ItemButton::setupButtonBg()
{
    this->bgOn = new ButtonBackground(this->buttonType, true, true, this->logicalSize, this->scene(), this);
    this->bgOff = new ButtonBackground(this->buttonType, false, false, this->logicalSize, this->scene(), this);
    this->bgHighlight = new ButtonBackground(this->buttonType,true, false, this->logicalSize, this->scene(), this);
    this->bgDisabled = new ButtonBackground(this->buttonType, true, true, this->logicalSize, this->scene(), this);
    this->setState(OFF);
}

void ItemButton::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    if (this->locked || this->state == DISABLED)
        return;

    if (this->state == OFF)
        this->setState(HIGHLIGHT);
}

void ItemButton::hoverLeaveEvent(QGraphicsSceneHoverEvent */*event*/)
{
    if (this->state == DISABLED)
        return;

    this->setState(OFF);
}

void ItemButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if (this->state == DISABLED)
        return;

    if (this->state == HIGHLIGHT || this->state == OFF)
        this->setState(ON);
}

void ItemButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->state == ON){
        this->setState(OFF);
        if (!this->locked && this->boundingRect().contains(event->pos())){
            //MenuManager::instance()->itemSelected(this->userCode, this->menuString);
        }
    }
}

void ItemButton::animationStarted(int)
{
    if (this->state == DISABLED)
        return;
    this->setState(OFF);
}



