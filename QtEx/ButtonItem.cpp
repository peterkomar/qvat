/***************************************************************************
 *                                                                         *
 *   This file is part of the FotoWall project,                            *
 *       http://code.google.com/p/fotowall                                 *
 *                                                                         *
 *   Copyright (C) 2007-2009 by Enrico Ros <enrico.ros@gmail.com>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "ButtonItem.h"
#include "private/system.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

ButtonItem::ButtonItem(const QString& label,Type type, const QIcon & icon, QGraphicsItem * parent)
    : QGraphicsItem(parent)
    , m_type(type)
    , m_icon(icon)
    , m_label(label)
	,b_press(false)
	,b_toggled(false)
	,m_state(UNCHECKED)
{
    setAcceptsHoverEvents(true);
	this->setCursor(Qt::PointingHandCursor);
    //if (type == Control)
    //    setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
		
	QFontMetrics fm(System::buttonFont());
	int f_width = fm.width(m_label);
	m_width = f_width > 64 ? fm.width(m_label) : 64;
	text_heigth = fm.height();
		
			
	text_x = (double)(m_width/2.0)-(double)(f_width/2.0);
	text_y = (double)height()+10;
}

ButtonItem::Type ButtonItem::buttonType() const
{
    return m_type;
}

int ButtonItem::width() const
{
    return m_width;
}

int ButtonItem::height() const
{
	return 64;
}

QRectF ButtonItem::boundingRect() const
{
	return QRectF(0, 0, m_width, 64);
}

void ButtonItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * /*widget*/)
{
    bool over = option->state & QStyle::State_MouseOver;
    if (over || b_toggled) {
		painter->save();
		if (System::useEightBitPalette)
			painter->setBrush(QColor(100, 100, 100));
		else {
			QLinearGradient outlinebrush(0, 0, 0, boundingRect().height());
			QLinearGradient brush(0, 0, 0, boundingRect().height());

			brush.setSpread(QLinearGradient::PadSpread);
			QColor highlight(255, 255, 255, 70);
			QColor shadow(0, 0, 0, 70);
			QColor sunken(220, 220, 220, 30);
			QColor normal1 = QColor(200, 170, 160, 50);
			QColor normal2 = QColor(50, 10, 0, 50);
			
			if(b_press)
			{
				outlinebrush.setColorAt(0.0f, shadow);
				outlinebrush.setColorAt(1.0f, highlight);
				brush.setColorAt(0.0f, sunken);
				painter->setPen(Qt::NoPen);
			}
			else
			{
				outlinebrush.setColorAt(1.0f, shadow);
				outlinebrush.setColorAt(0.0f, highlight);
				brush.setColorAt(0.0f, normal1);
				brush.setColorAt(1.0f, normal2);
				painter->setPen(QPen(outlinebrush, 1));
			}
			painter->setBrush(brush);
		}
		
		
		painter->drawRect(boundingRect().adjusted(-2, -2, 2, text_heigth));
		//painter->fillRect(boundingRect().adjusted(-1, -1, 1, text_heigth), Qt::white);
		painter->restore();
    }
    if (!m_icon.isNull()) {
        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
        //m_icon.paint(painter, boundingRect().toRect(), Qt::AlignCenter, over ? QIcon::Active : QIcon::Normal);
		m_icon.paint(painter, (m_width-64)/2,0,64,64, Qt::AlignCenter, over ? QIcon::Active : QIcon::Normal);
        painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
    }
			
		
	painter->save();
	painter->setFont(System::buttonFont());
	painter->setPen(System::buttonText);
	painter->drawText(text_x,text_y, m_label);
	painter->restore();
}

void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	b_press = true;
		
    update();
    //emit pressed();
}

void ButtonItem::setToggled(bool b)
{
	b_toggled = b;
	b_press = b;
}

void ButtonItem::setCheckable(bool b)
{
	if(b)
		m_state = CHECKED;
	else
		m_state = UNCHECKED;
}


void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    //event->accept();
    if(m_state == CHECKED)
	{
            if(b_toggled)
            {
                b_press = false;
                b_toggled = false;
            }
			else
			    b_toggled = true;
			
	}
        else
            b_press = false;

	update();
	
	emit clicked(this);
}


