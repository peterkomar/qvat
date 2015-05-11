#include "itemtext.h"
#include "private/system.h"

ItemText::ItemText(const QString &text, const QFont &font, const QColor &textColor,
                           float textWidth, QGraphicsScene *scene, QGraphicsItem *parent, const QColor &bgColor)
                           : Item(scene, parent)
{
    this->text = text;
    this->font = font;
    this->textColor = textColor;
    this->bgColor = bgColor;
    this->textWidth = textWidth;
}

void ItemText::setText(const QString &text)
{
    this->text = text;
    this->update();
}

QImage *ItemText::createImage(const QMatrix &matrix) const
{
    float sx = qMin(matrix.m11(), matrix.m22());
    float sy = matrix.m22() < sx ? sx : matrix.m22();

    QGraphicsTextItem textItem(0, 0);
    textItem.setHtml(this->text);
    textItem.setTextWidth(this->textWidth);
    textItem.setFont(this->font);
    textItem.setDefaultTextColor(this->textColor);
    //textItem.document()->setDocumentMargin(2);

    float w = textItem.boundingRect().width();
    float h = textItem.boundingRect().height();
    QImage *image = new QImage(int(w * sx), int(h * sy), QImage::Format_ARGB32_Premultiplied);
    image->fill(QColor(0, 0, 0, 0).rgba());
    QPainter painter(image);
    painter.scale(sx, sy);
    QStyleOptionGraphicsItem style;
    textItem.paint(&painter, &style, 0);
    return image;
}


