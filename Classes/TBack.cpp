#include "TBack.h"

bool TBack::init()
{
	Layer::init();
	setLocalZOrder(100);
	Menu * menu = Menu::create();
	MenuItemImage * item = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref*){
		Director::getInstance()->popScene();
	});

	menu->addChild(item);

	item->setPosition(winSize.width / 2 - item->getBoundingBox().size.width / 2,
		item->getBoundingBox().size.height / 2 - winSize.height / 2);

	addChild(menu);
	return true;
}