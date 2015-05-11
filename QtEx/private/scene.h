#ifndef SCENE_H
#define SCENE_H

#include <QtGui>

class Scene : public QGraphicsScene
{
public:
	Scene(QObject *parent) : QGraphicsScene(parent){};

/*protected:
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget);*/
};

#endif // SCENE_H

