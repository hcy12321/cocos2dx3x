#include "TMenu.h"
#include "TBack.h"
#include "T01CPP11.h"
#include "T02Vector.h"
#include "T03Map.h"
#include "T04Label.h"
#include "T05Touch.h"
#include "T06Box2D.h"
#include "T07PhysicsWorld.h"

static const char * title[] = {
	"T01CPP11",
	"T02Vector",
	"T03Map",
	"T04Label",
	"T05Touch",
	"T06Box2D",
	"T07PhysicsWorld"
};

bool TMenu::init()
{
	Layer::init();

	Menu * menu = Menu::create();
	addChild(menu);
	
	for (int i = 0; i < sizeof(title) / sizeof(*title); ++i)
	{
		MenuItemFont * item = MenuItemFont::create(title[i], [](Ref * sender){
			MenuItem * item = (MenuItem *)sender;
			int i = item->getTag() - 1000;
			Layer * l = NULL;
			if (title[i] == "T01CPP11") l = T01CPP11::create();
			else if (title[i] == "T02Vector") l = T02Vector::create();
			else if (title[i] == "T03Map") l = T03Map::create();
			else if (title[i] == "T04Label") l = T04Label::create();
			else if (title[i] == "T05Touch") l = T05Touch::create();
			else if (title[i] == "T06Box2D") l = T06Box2D::create();
			else if (title[i] == "T07PhysicsWorld") l = T07PhysicsWorld::create();
			if (l != NULL)
			{
				TBack * b = TBack::create();
				//Scene * s = Scene::create();
				Scene * s = Scene::createWithPhysics(); // 3.x 物理世界
				PhysicsWorld * world = s->getPhysicsWorld();
				world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
				s->addChild(b);
				s->addChild(l);
				Director::getInstance()->pushScene(s);

			}
		});
		menu->addChild(item);
		item->setTag(1000 + i);
	}

	menu->alignItemsVertically();

	// 触摸
	auto ev = EventListenerTouchOneByOne::create();
	//ev->onTouchBegan = std::bind(&TMenu::touchBegan, this, std::placeholders::_1, std::placeholders::_2);
	ev->onTouchBegan = CC_CALLBACK_2(TMenu::touchBegan, this);
	ev->onTouchMoved = [&](Touch * touch, Event *){
		setPositionY(getPositionY() + touch->getDelta().y);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);

	return true;
}

bool TMenu::touchBegan(Touch *, Event *)
{
	return true;
}