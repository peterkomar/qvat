#ifndef ITEM_BUTTON_H
#define ITEM_BUTTON_H

#include <QtGui>
#include <QtCore/qobject.h>
#include "item.h"

class ItemAnimation;
class ButtonBackground;

class ItemButton : public QObject, public Item
{
	Q_OBJECT
public:
    enum BUTTONTYPE {SIDEBAR, PANEL, IMAGE, UP, DOWN};
    enum STATE {ON, OFF, HIGHLIGHT, DISABLED};

	ItemButton(const QString &text, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0, BUTTONTYPE color = SIDEBAR);
	ItemButton(const QString &pathPixmap, const QString &text="", QGraphicsScene *scene = 0, QGraphicsItem *parent = 0, BUTTONTYPE color = SIDEBAR);
    ~ItemButton();

    QRectF boundingRect() const;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = 0){};
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void animationStarted(int id = 0);
    void prepare();
    void setState(STATE state);
    void setDisabled(bool disabled);

private:
	void ItemInit(BUTTONTYPE type);
    void setupButtonBg();
    void setupButton();
	
    ButtonBackground *bgOn;
    ButtonBackground *bgOff;
    ButtonBackground *bgHighlight;
    ButtonBackground *bgDisabled;

    BUTTONTYPE buttonType;
    QString buttonLabel;
	QImage* buttonPixmap;
    QSize logicalSize;

    STATE state;

Q_SIGNALS:
	void clicked();
};

#endif // ITEM_BUTTON_H

