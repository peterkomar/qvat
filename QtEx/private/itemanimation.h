#ifndef ITEM_ANIMATION_H
#define ITEM_ANIMATION_H

#include <QtGui>

class ButtonItem;

class ItemAnimation : public QGraphicsItemAnimation
{
public:
	enum INOROUT {ANIM_IN, ANIM_OUT, ANIM_UNSPECIFIED};

    ItemAnimation(ButtonItem *item, INOROUT inOrOut = ANIM_UNSPECIFIED);
    ~ItemAnimation();

    void play(bool fromStart = true);
        
	void setDuration(int duration);
    void setDuration(float duration){ setDuration(int(duration)); };
    void setCurrentTime(int ms);
    void setStartPos(const QPointF &pos);
	//bool isRuning();
     
    ButtonItem *getItem();
   
    QTimeLine *timeline;
    QPointF startPos;
    bool fromStart;
    INOROUT inOrOut;
};

#endif // ITEM_ANIMATION_H



