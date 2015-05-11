#ifndef ITEM_H
#define ITEM_H

#include <QtGui>

class ItemAnimation;

class SharedImage
{
public:
    SharedImage() : refCount(0), image(0){};
    ~SharedImage()
    {
        delete image;
    }

    int refCount;
    QImage *image;
    QMatrix matrix;
    QRectF unscaledBoundingRect;
};

class Item : public QGraphicsItem
{
public:
    Item(QGraphicsScene *scene = 0, QGraphicsItem *parent = 0);
    virtual ~Item();

    virtual void animationStarted(int id = 0){ Q_UNUSED(id); };
    virtual void animationStopped(int id = 0){ Q_UNUSED(id); };
    virtual void prepare(){};
    void setRecursiveVisible(bool visible);
    void useSharedImage(const QString &hashKey);
    static void setMatrix(const QMatrix &matrix);
    virtual QRectF boundingRect() const; // overridden
    
    qreal opacity;
    bool locked;
    ItemAnimation *currentAnimation;
    bool noSubPixeling;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option = 0, QWidget *widget = 0); // overridden
    virtual QImage *createImage(const QMatrix &) const { return 0; };
    virtual bool collidesWithItem(const QGraphicsItem *, Qt::ItemSelectionMode) const { return false; };
    bool prepared;

private:
    SharedImage *sharedImage;
    QString hashKey;
    bool neverVisible;
    bool validateImage();

    static QHash<QString, SharedImage *> sharedImageHash;
    static QMatrix matrix;
};

#endif // ITEM_H

