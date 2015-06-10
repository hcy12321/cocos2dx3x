#include "T09Joint.h"


bool T09Joint::init()
{
	Layer::init();
	m_A = m_B = m_C = NULL;
	return true;
}
void T09Joint::onEnter()
{
	Layer::onEnter();

	PhysicsBody * bodyA = NULL;
	PhysicsBody * bodyB = NULL;
	{
		PhysicsBody * body = PhysicsBody::createCircle(20);
		bodyA = body;
		Sprite * sprite = Sprite::create();
		m_A = sprite;
		sprite->setContentSize(Size(40, 40));
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2 - 50, winSize.height / 2 + 100);
		addChild(sprite);
	}
	{
		PhysicsBody * body = PhysicsBody::createBox(Size(40, 40));
							// PhysicsBody::createEdgeBox(Size(40, 40));
		bodyB = body;
		Sprite * sprite = Sprite::create();
		m_B = sprite;
		sprite->setContentSize(Size(40, 40));
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2 + 50, winSize.height / 2 + 100);
		addChild(sprite);
	}

	{
		PhysicsBody * body = PhysicsBody::createEdgeBox(winSize, PhysicsMaterial(1.0f, 1.0f, 1.0f)); 
		Sprite * sprite = Sprite::create();
		addChild(sprite);
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);
	}
	PhysicsJoint * joint =
		//	PhysicsJointDistance::construct(bodyA, bodyB, Vec2(0, 0), Vec2(0, 0));
		//	PhysicsJointSpring::construct(bodyA, bodyB, Vec2(0, 0), Vec2(0, 0), 3000.0f, 0.5f);
		//  PhysicsJointPin::construct(bodyA, bodyB, Vec2(winSize.width / 2, winSize.height / 2));
		PhysicsJointMotor::construct(bodyA, bodyB, M_PI_2);
	getPhysicsWorld()->addJoint(joint);
	{
		auto ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [&](Touch * touch, Event *)
		{
			Point pt = touch->getLocation();
			if (m_A->getBoundingBox().containsPoint(pt))
			{
				m_C = m_A;
				return true;
			}
			if (m_B->getBoundingBox().containsPoint(pt))
			{
				m_C = m_B;
				return true;
			}

			return false;
		};

		ev->onTouchEnded = [&](Touch * touch, Event *){
			Vec2 pt = touch->getLocation() - touch->getStartLocation();
			m_C->getPhysicsBody()->setVelocity(Vec2(pt));
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}
	
}