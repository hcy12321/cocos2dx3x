#include "T08RayCast.h"

bool T08RayCast::init()
{
	Layer::init();
	// 创建猫， 不是body，只是一个精灵
	{
		m_cat = Sprite::create("CloseNormal.png");
		addChild(m_cat);
		m_cat->setPosition(winSize.width / 2, winSize.height / 2);
	}
	// 投放食物，食物必须是body
	{
		auto ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [&](Touch * touch, Event *){
			Vec2 pt = touch->getLocation();
			PhysicsBody * body = PhysicsBody::createCircle(10);
			Sprite * sprite = Sprite::create();
			sprite->setPhysicsBody(body);
			addChild(sprite);

			sprite->setPosition(pt);
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	}

	scheduleUpdate();
	m_nangel = 0;
	m_ndistance = 100;
	m_fnearDis = m_ndistance + 100;
	m_drawNode = NULL;
	m_food = NULL;
	return true;
}
void T08RayCast::onEnter()
{
	Layer::onEnter();
	Scene * scene = (Scene *)getParent();
	// 设置重力为0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
}

void T08RayCast::update(float delta)
{
	Scene * scene = (Scene *)getParent();
	PhysicsWorld * world = scene->getPhysicsWorld();
	Vec2 start = m_cat->getPosition();
	Vec2 end;
	end.x = start.x + sinf(m_nangel / 180.0f * M_PI) * m_ndistance;
	end.y = start.y + cosf(m_nangel / 180.0f * M_PI) * m_ndistance;

	if (m_drawNode != NULL) m_drawNode->removeFromParent();
	m_drawNode = DrawNode::create();
	m_drawNode->drawSegment(start, end, 1, Color4F(1, 0, 0, 1));
	addChild(m_drawNode);

	auto callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void *data){
		if (info.shape == NULL)
			return true;
		float dis = info.contact.getDistance(m_cat->getPosition());
		if (dis < m_fnearDis)
		{
			m_fnearDis = dis;
			m_food = info.shape;
		}
		// 扫描到一个就不要在继续了
		return false;
	};
	world->rayCast(callback, start, end, NULL);
	m_nangel += 2;
	if (m_nangel == 360)
	{
		if (m_food != NULL)
		{
			// 吃掉食物
			Node * node = m_food->getBody()->getNode();
			m_cat->setPosition(node->getPosition());
			node->removeFromParent();
			m_food = NULL;
			m_fnearDis = m_ndistance + 100;
		}
		m_nangel = 0;
	}
}