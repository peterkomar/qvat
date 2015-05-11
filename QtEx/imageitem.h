#ifndef IMAGE_ITEM_H
#define IMAGE_ITEM_H

#include <QtGui>
#include "item.h"

class ImageItem : public Item
{
public:
    ImageItem(const QImage &image, int maxWidth, int maxHeight, QGraphicsScene *scene = 0, QGraphicsItem *parent = 0,
         bool adjustSize = false, float scale = 1.0f);

    bool adjustSize;
    float scale;
	int image_witdh;
	int image_heigdh;
protected:
    QImage *createImage(const QMatrix &matrix) const;

private:
    QImage image;
    int maxWidth;
    int maxHeight;
	
	void set_alpha_image(const QImage &image);
};

#endif // IMAGE_ITEM_H

