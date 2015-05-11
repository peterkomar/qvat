#ifndef ITEM_TEXT_H
#define ITEM_TEXT_H

#include <QtGui>
#include "item.h"

class ItemText : public Item
{
public:
    ItemText(const QString &text, const QFont &font, const QColor &textColor,
        float textWidth, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0, const QColor &bgColor = QColor());
    void setText(const QString &text);
       
protected:
    virtual QImage *createImage(const QMatrix &matrix) const; // overridden   

private:
    float textWidth;
    QString text;
    QFont font;
    QColor textColor;
    QColor bgColor;
};

#endif // ITEM_TEXT_H

