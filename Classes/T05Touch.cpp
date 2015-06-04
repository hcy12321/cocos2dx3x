#include "T05Touch.h"


bool T05Touch::init()
{
	Layer::init();
	{
		// һ��ʹ�����ַ�ʽ����һ��Node�����
		EventListenerTouchOneByOne * ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [](Touch *, Event*){
			return true;
		};
		ev->onTouchEnded = CC_CALLBACK_2(T05Touch::TouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	/*
	{
		// �������ȼ��ķ�ʽ��ʹ�ñȽ���
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