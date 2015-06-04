#include "T06Box2D.h"

#define PTM_RATIO 32.0f

bool T06Box2D::init()
{
	Layer::init();

	// 创建世界
	b2Vec2 gravity(0, -9.8f);
	m_world = new b2World(gravity);
	{
		// 定义
		b2BodyDef def;
		// 设置可动
		def.type = b2_dynamicBody;
		// 设置位置
		def.position.Set(winSize.width / 2 / PTM_RATIO, winSize.height / 2 / PTM_RATIO);
		// g根据定义创建形体，并关联到世界
		b2Body * body = m_world->CreateBody(&def);

		// 控制受力
		body->SetLinearVelocity(b2Vec2(10, 20));
		// 创建显示精灵
		Sprite * sprite = Sprite::create("CloseNormal.png");
		addChild(sprite);
		sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);

		// 设置body的形状，让ta和sprite相一致
		b2CircleShape shape;
		shape.m_radius = sprite->getContentSize().width / 2 / PTM_RATIO;
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f); // 密度系数
		fixture->SetFriction(1.0f); // 摩擦系数
		fixture->SetRestitution(1.0f); // 弹性系数
		// 关联精灵
		body->SetUserData(sprite);


	}
	// 加个地板
	{
		b2BodyDef def;
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// 加个天花板
	{
		b2BodyDef def;
		def.position.Set(0, winSize.height / PTM_RATIO);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// 左挡板
	{
		b2BodyDef def;
		//def.position.Set(0, winSize.height / PTM_RATIO);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// 右挡板
	{
		b2BodyDef def;
		def.position.Set(winSize.height / PTM_RATIO, 0);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// 球拍
	{
		b2BodyDef def;
		def.position.Set(winSize.width / 2 / PTM_RATIO, winSize.height / 4 / PTM_RATIO);
		b2Body * body = m_world->CreateBody(&def);
		m_bat = body;
		Sprite * sprite = Sprite::create("bat.png");
		body->SetUserData(sprite);
		sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);
		Size batSize = Size(100, 30);
		Size content = sprite->getContentSize();
		sprite->setScale(batSize.width / content.width, batSize.height / content.height);
		addChild(sprite);

		b2PolygonShape shape;
		shape.SetAsBox(batSize.width / 2 / PTM_RATIO, batSize.height / 2 / PTM_RATIO);
		b2Fixture *fixture = body->CreateFixture(&shape, 1.0f);
		fixture->SetRestitution(1.0f);
		
		// touch
		EventListenerTouchOneByOne * ev = EventListenerTouchOneByOne::create();
		ev->onTouchBegan = [](Touch *, Event *){
			return true;
		};
		ev->onTouchMoved = [&](Touch * touch, Event *){
			float dx = touch->getDelta().x / PTM_RATIO;
			b2Vec2 pos = m_bat->GetPosition();
			pos.x += dx;
			m_bat->SetTransform(pos, 0);
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);

	}

	scheduleUpdate();
	return true;
}

void T06Box2D::update(float dt)
{
	// 时间在流逝
	m_world->Step(dt, 8, 1);
	// 遍历这个世界的body
	b2Body * body = m_world->GetBodyList();
	while (body != NULL)
	{
		// 设置body相关的精灵的位置
		Sprite * sprite = (Sprite *)body->GetUserData();
		if (sprite != NULL)
		{
			sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);
			sprite->setRotation(body->GetAngle() * 180 / M_PI);
		}


		body = body->GetNext();
		
	}
}
