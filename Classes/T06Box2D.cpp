#include "T06Box2D.h"

#define PTM_RATIO 32.0f

bool T06Box2D::init()
{
	Layer::init();

	// ��������
	b2Vec2 gravity(0, -9.8f);
	m_world = new b2World(gravity);
	{
		// ����
		b2BodyDef def;
		// ���ÿɶ�
		def.type = b2_dynamicBody;
		// ����λ��
		def.position.Set(winSize.width / 2 / PTM_RATIO, winSize.height / 2 / PTM_RATIO);
		// g���ݶ��崴�����壬������������
		b2Body * body = m_world->CreateBody(&def);

		// ��������
		body->SetLinearVelocity(b2Vec2(10, 20));
		// ������ʾ����
		Sprite * sprite = Sprite::create("CloseNormal.png");
		addChild(sprite);
		sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);

		// ����body����״����ta��sprite��һ��
		b2CircleShape shape;
		shape.m_radius = sprite->getContentSize().width / 2 / PTM_RATIO;
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f); // �ܶ�ϵ��
		fixture->SetFriction(1.0f); // Ħ��ϵ��
		fixture->SetRestitution(1.0f); // ����ϵ��
		// ��������
		body->SetUserData(sprite);


	}
	// �Ӹ��ذ�
	{
		b2BodyDef def;
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// �Ӹ��컨��
	{
		b2BodyDef def;
		def.position.Set(0, winSize.height / PTM_RATIO);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// �󵲰�
	{
		b2BodyDef def;
		//def.position.Set(0, winSize.height / PTM_RATIO);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// �ҵ���
	{
		b2BodyDef def;
		def.position.Set(winSize.height / PTM_RATIO, 0);
		b2Body * body = m_world->CreateBody(&def);
		b2EdgeShape shape;
		shape.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
		b2Fixture * fixture = body->CreateFixture(&shape, 1.0f);
	}
	// ����
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
	// ʱ��������
	m_world->Step(dt, 8, 1);
	// ������������body
	b2Body * body = m_world->GetBodyList();
	while (body != NULL)
	{
		// ����body��صľ����λ��
		Sprite * sprite = (Sprite *)body->GetUserData();
		if (sprite != NULL)
		{
			sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);
			sprite->setRotation(body->GetAngle() * 180 / M_PI);
		}


		body = body->GetNext();
		
	}
}
