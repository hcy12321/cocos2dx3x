#include "T05Touch.h"


bool T05Touch::init()
{
	Layer::init();
	{
		// 一般使用这种方式，和一个Node相关联
		EventListenerTouchOneByOne * ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [](Touch *, Event*){
			return true;
		};
		ev->onTouchEnded = CC_CALLBACK_2(T05Touch::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	/*
	{
		// 固有优先级的方式，使用比较少
		EventListenerTouchOneByOne * ev = EventListenerTouchOneByOne::create();
		ev->setSwallowTouches(true);
		ev->onTouchBegan = [](Touch *, Event *){return true; };
		_eventDispatcher->addEventListenerWithFixedPriority(ev, -128);
	}
	*/
	{
		Sprite* node = Sprite::create();
		addChild(node);
		EventListenerTouchOneByOne * ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [](Touch * touch, Event*){
			Vec2 pt = touch->getLocation();
			CCLog("Sprite is touched, pt.x=%f,pt.y=%f", pt.x, pt.y);
			return true;
		};
		ev->onTouchEnded = CC_CALLBACK_2(T05Touch::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, node);
	}
	{
		EventListenerTouchAllAtOnce * ev = EventListenerTouchAllAtOnce::create();
		ev->onTouchesBegan = [](const std::vector<Touch*>&,Event *){

		};
	}
	return true;
}

void T05Touch::TouchEnded(Touch *, Event *)
{

}