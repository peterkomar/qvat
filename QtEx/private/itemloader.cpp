//
// C++ Implementation: itemloader
//
// Description: 
//
//
// Author: Peter <marcusk@i.ua>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "itemloader.h"
#include "../itembutton.h"
#include "itemanimation.h"

#include <QtGui>

ItemLoader *ItemLoader::pInstance = 0;

ItemLoader * ItemLoader::instance()
{
	if (!ItemLoader::pInstance)
		ItemLoader::pInstance = new ItemLoader();
	return ItemLoader::pInstance;
}

ItemLoader::ItemLoader(QObject *parent)
 : QObject(parent)
{
}


ItemLoader::~ItemLoader()
{
}

void ItemLoader::init(IMenu* list_items)
{
	for(int i=0; i<list_items->size(); i++)
	{
		ItemAnimation *ani = static_cast<ItemAnimation *>(list_items->at(i));
		ani->play(true);
	}
}
