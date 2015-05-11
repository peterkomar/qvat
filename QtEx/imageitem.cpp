#include "imageitem.h"
#include "private/system.h"

ImageItem::ImageItem(const QImage &image, int maxWidth, int maxHeight, QGraphicsScene *scene,
        QGraphicsItem *parent, bool adjustSize, float scale) : Item(scene, parent)
{
    if(!System::tansparentIcons)
		this->image = image;
	else
		set_alpha_image(image);
	
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    this->adjustSize = adjustSize;
    this->scale = scale;
	this->image_witdh = image.width();
	this->image_heigdh = image.height();
}

void ImageItem::set_alpha_image(const QImage &image)
{
	QImage *img = new QImage(image.size(),QImage::Format_ARGB32_Premultiplied);
	QImage aimg = image.createHeuristicMask();//createAlphaMask(Qt::MonoOnly);
	
	img->fill(QColor(0, 0, 0, 0).rgba());
	QPainter p(img);
	p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	
	for(int i = 0;i<image.height();i++)
		for(int j=0;j<image.width();j++)
	{
		QColor col(image.pixel(i,j));
		QColor acol = (aimg.pixel(i,j));
		if(col != acol)
		{
		  col.setAlpha(System::valueTransparent);
		  p.setPen(QPen(col));
		  p.drawPoint(i,j);
	    }
	}
	
	p.end();
			
	this->image = *img;
	
	delete img;
}

QImage *ImageItem::createImage(const QMatrix &matrix) const
{
    QImage *original = new QImage(image);
    if (original->isNull()){
        return original; // nothing we can do about it...
    }

    QPoint size = matrix.map(QPoint(this->maxWidth, this->maxHeight));
    float w = size.x(); // x, y is the used as width, height
    float h = size.y();

    // Optimization: if image is smaller than maximum allowed size, just return the loaded image
    if (original->size().height() <= h && original->size().width() <= w && !this->adjustSize && this->scale == 1)
        return original;

    // Calculate what the size of the final image will be:
    w = qMin(w, float(original->size().width()) * this->scale);
    h = qMin(h, float(original->size().height()) * this->scale);

    float adjustx = 1.0f;
    float adjusty = 1.0f;// щоб зміни по висоті були не менші за зміни по ширині, щоб малюнок
						//не викривлявся (зображення буде викривлятись по висоті), 
	// для того що не викривлялось потрібно adjusty = adjustx
    if (this->adjustSize){
        adjustx = qMin(matrix.m11(), matrix.m22());
        //adjusty = matrix.m22() < adjustx ? adjustx : matrix.m22();
		adjusty = adjustx;
		w *= adjustx;
        h *= adjusty;
    }

    // Create a new image with correct size, and draw original on it
    QImage *image = new QImage(int(w+2), int(h+2), QImage::Format_ARGB32_Premultiplied);
    image->fill(QColor(0, 0, 0, 0).rgba());
    QPainter painter(image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if (this->adjustSize)
        painter.scale(adjustx, adjusty);
    if (this->scale != 1)
       painter.scale(this->scale, this->scale);
		
    painter.drawImage(0, 0, *original);
	    
    delete original;
    return image;
}
