#include "item.h"
#include "private/itemloader.h"
#include "private/system.h"

QHash<QString, SharedImage *> Item::sharedImageHash;
QMatrix Item::matrix;

Item::Item(QGraphicsScene *scene, QGraphicsItem *parent) : QGraphicsItem(parent, scene)
{
    this->opacity = 1.0;
    this->locked = false;
    this->prepared = false;
    this->neverVisible = false;
    this->noSubPixeling = false;
    this->currentAnimation = 0;
    this->sharedImage = new SharedImage();
    ++this->sharedImage->refCount;
}

Item::~Item()
{
    if(--this->sharedImage->refCount == 0){
        if (!this->hashKey.isEmpty())
            Item::sharedImageHash.remove(this->hashKey);
        delete this->sharedImage;
    }
}

void Item::setRecursiveVisible(bool visible){
    
    this->setVisible(visible);
    QList<QGraphicsItem *> c = children();
    for (int i=0; i<c.size(); i++){
          c[i]->setVisible(visible);
    }
}

void Item::setMatrix(const QMatrix &matrix)
{
    Item::matrix = matrix;
}

void Item::useSharedImage(const QString &hashKey)
{
    this->hashKey = hashKey;
    if (!sharedImageHash.contains(hashKey))
        sharedImageHash.insert(hashKey, this->sharedImage);
    else {
        if(--this->sharedImage->refCount == 0)
            delete this->sharedImage;
        this->sharedImage = sharedImageHash.value(hashKey);
        ++this->sharedImage->refCount;
    }
}

bool Item::validateImage()
{
    if ((this->sharedImage->matrix != Item::matrix) || !(this->sharedImage->image)){
       // (Re)create image according to new matrix
       delete this->sharedImage->image;
       this->sharedImage->image = 0;
       this->sharedImage->matrix = Item::matrix;

        // Let subclass create and draw a new image according to the new matrix
       QImage *image = this->createImage(Item::matrix);
	   if (image){
           this->sharedImage->unscaledBoundingRect = this->sharedImage->matrix.inverted().mapRect(image->rect());
           
		   this->sharedImage->image = image;
            
           return true;
        } else
           return false;
    }
    return true;
}

QRectF Item::boundingRect() const
{
    const_cast<Item *>(this)->validateImage();
    return this->sharedImage->unscaledBoundingRect;
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    if (this->validateImage()){

        bool wasSmoothPixmapTransform = painter->testRenderHint(QPainter::SmoothPixmapTransform);
        painter->setRenderHint(QPainter::SmoothPixmapTransform);

        QMatrix m = painter->worldMatrix();
        painter->setWorldMatrix(QMatrix());
        float x = this->noSubPixeling ? qRound(m.dx()) : m.dx();
        float y = this->noSubPixeling ? qRound(m.dy()) : m.dy();
           
		painter->drawImage(QPointF(x, y), *this->sharedImage->image);
        

        if (!wasSmoothPixmapTransform) {
            painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
        }

    }
}
