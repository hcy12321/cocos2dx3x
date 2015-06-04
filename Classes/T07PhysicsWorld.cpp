#include "T07PhysicsWorld.h"

bool T07PhysicsWorld::init()
{
	Layer::init();

	PhysicsBody * bodyA;
	PhysicsBody * bodyB;

	{
		PhysicsBody * body = PhysicsBody::createCircle(20, PhysicsMaterial(1.0f, 1.0f, 0.0f));
		bodyA = body;
		//Sprite * sprite = Sprite::create("CloseNormal.png");

		Sprite * sprite = Sprite::create();
		sprite->setPhysicsBody(body);
		addChild(sprite);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);

		body->setVelocity(Vect(100, 200)); // 设置初始速度
	}
	{
		PhysicsBody * body = PhysicsBody::createEdgeBox(winSize, PhysicsMaterial(1.0f, 1.0f, 0.0f));
		bodyB = body;
		Sprite * sprite = Sprite::create();
		addChild(sprite);
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);

	}
	{
		bodyA->setContactTestBitmask(0x1);
		bodyB->setContactTestBitmask(0x1);
		bodyA->setGroup(1);
		bodyB->setGroup(1);

		auto * ev = EventListenerPhysicsContactWithBodies::create(bodyA, bodyB);
		ev->onContactBegin = [](PhysicsContact& contact){
			CCLog("Began Contact ...");
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	{
		auto * ev = EventListenerPhysicsContactWithShapes::create(bodyA->getShapes().at(0),
			bodyB->getShapes().at(0));
		ev->onContactBegin = [](PhysicsContact& contact){
			CCLog("Shape begin Contact ...");
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	{
		auto * ev = EventListenerPhysicsContactWithGroup::create(1);
		ev->onContactBegin = [](PhysicsContact& contact){
			CCLog("Group begin Contact ...");
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	//getScene()->getPhysicsWorld()->getGravity();
	return true;
}

inline Scene * T07PhysicsWorld::getScene()
{
	return (Scene*)getParent();
}