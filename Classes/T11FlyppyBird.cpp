#include "T11FlyppyBird.h"
#include "SceneFlyGame.h"

bool T11FlyppyBird::init()
{
	Layer::init();

	Menu * menu = Menu::create();
	MenuItem * item = MenuItemFont::create("Start Game", [](Ref*){
		Director::getInstance()->pushScene(SceneFlyGame::create());
	});
	menu->addChild(item);
	addChild(menu);

	return true;
}