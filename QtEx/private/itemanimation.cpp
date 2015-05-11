#include "itemanimation.h"
#include "../ButtonItem.h"
#include "system.h"

ItemAnimation::ItemAnimation(ButtonItem *item, INOROUT inOrOut)
{
	this->inOrOut = inOrOut;
	this->timeline = new QTimeLine(5000);
	this->timeline->setFrameRange(0, 2000);
	this->timeline->setUpdateInterval(int(1000.0/System::fps));
	setTimeLine(this->timeline);
	setItem(item);
}

ItemAnimation::~ItemAnimation()
{
    delete this->timeline;
}

void ItemAnimation::setStartPos(const QPointF &pos){
    this->startPos = pos;
}

void ItemAnimation::setDuration(int duration)
{
    duration = int(duration * System::animSpeed);
    this->timeline->setDuration(duration);
}

void ItemAnimation::setCurrentTime(int ms)
{
    this->timeline->setCurrentTime(ms);
}

/*bool ItemAnimation::isRuning()
{
	return this != getItem()->currentAnimation;
}*/


void ItemAnimation::play(bool fromStart)
{
    this->fromStart = fromStart;
    
    QPointF currPos = this->getItem()->pos();
	
	if (this->getItem()->isVisible())
         this->setPosAt(0.0, currPos);
    else
         this->setPosAt(0.0, this->startPos);

     if (this->fromStart){
          this->timeline->setCurrentTime(0);
           this->getItem()->setPos(this->posAt(0));
     }
   
	if (this->inOrOut == ANIM_IN)
        this->getItem()->setVisible(true);
	
	this->timeline->start();
	//this->getItem()->animationStarted(this->inOrOut);
}


ButtonItem *ItemAnimation::getItem()
{
	return (ButtonItem *) this->item();
}





