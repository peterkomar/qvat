#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <QObject>
#include <QList>

class ItemAnimation;
typedef QList<ItemAnimation *> IMenu;
/**
	@author Peter <marcusk@i.ua>
*/
class ItemLoader : public QObject
{
Q_OBJECT
public:
	enum ITEM_MOVE_FROM {AUTO, LEFT, RIGHT, UP, DOWN};
	
	static ItemLoader *instance();
    
    ~ItemLoader();
	void init(IMenu* list_items);

private:
	ItemLoader(QObject *parent = 0);
		
	static ItemLoader *pInstance;
};

#endif
