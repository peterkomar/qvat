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

#ifndef __ButtonItem_h__
#define __ButtonItem_h__

#include <QGraphicsItem>
#include <QIcon>
#include <QBrush>
#include <QPointF>

class ButtonItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    public:
		enum Type {PANEL, ITEM};
		enum State {CHECKED, UNCHECKED};
        ButtonItem(const QString& label, Type type, const QIcon & icon, QGraphicsItem * parent);

        Type buttonType() const;
        int width() const;
        int height() const;

        // set data
        void setCheckable( bool b = true );
        void setToggled( bool b = true );
        void setIcon(const QIcon& icon);
        void setLabel(const QString& label);
		
        QRectF boundingRect() const;
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
        
    Q_SIGNALS:
        void pressed();
        void clicked(ButtonItem *);
        
    private:
        Type        m_type;
        QIcon       m_icon;
        QPointF     m_startPos;
        QString     m_label;
        int         m_width;
        int         text_heigth;
        double      text_x;
        double      text_y;
        bool        b_press;
        bool        b_toggled;
        State       m_state;
};

#endif
