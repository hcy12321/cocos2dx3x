#include "SceneFlyGame.h"
#include "TBack.h"

bool SceneFlyGame::init()
{
	Scene::initWithPhysics();
	// 显示边框线
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// 返回按钮
	Node * back = TBack::create();
	addChild(back);
	back->setLocalZOrder(100);
	// 创建一个鸟
	Sprite * bird = Sprite::create();
	m_bird = bird;
	bird->setContentSize(Size(16, 16));
	addChild(bird);
	bird->setPosition(winSize.width / 4, winSize.height / 2);
	bird->setScale(2, 1);

	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage("flyFishRight.png");
	Vector<SpriteFrame *> frames;
	for (int i = 0; i < 6; i++)
	{
		SpriteFrame * frame = SpriteFrame::createWithTexture(texture, Rect(i * 16, 0, 16, 16));
		frames.pushBack(frame);
	}
	Animation * animation = Animation::createWithSpriteFrames(frames, .1f);
	Animate * animate = Animate::create(animation);
	bird->runAction(RepeatForever::create(animate));

	// 给鸟加一个body
	Size size = bird->getBoundingBox().size;
	Point pts[] = { 
		Point(-size.width / 2, -size.height / 2),
		//Point(-size.width / 2, size.height / 2),
		Point(-size.width / 2, 0),
		Point(0, size.height / 2),
		Point(size.width / 2, size.height / 2),
		Point(size.width / 2, -size.height / 2)
	};
	PhysicsBody * body = PhysicsBody::createPolygon(pts, 5);
	bird->setPhysicsBody(body);
	body->setGroup(1);
	body->setContactTestBitmask(1); // 碰撞标志位

	// 添加边框
	{
		PhysicsBody * body = PhysicsBody::createEdgeBox(winSize, PhysicsMaterial(1.0f, 1.0f, 1.0f));
		Sprite * sprite = Sprite::create();
		addChild(sprite);
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);
		body->setContactTestBitmask(1);
	}
	// 鸟上升
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [&](Touch*, Event *){
		m_press = true;
		return true;
	};
	ev->onTouchEnded = [&](Touch*, Event *){
		m_press = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
	m_press = false;
	schedule(schedule_selector(SceneFlyGame::fly));
	
	//碰撞检测
	auto evCollision = EventListenerPhysicsContactWithGroup::create(1);

	evCollision->onContactBegin = [&](PhysicsContact & contact){
		m_dead = true;
		// 去除连续的碰撞检测
		m_bird->getPhysicsBody()->setGroup(0);
		return true;
	};
	m_dead = false;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(evCollision, this);

	schedule(schedule_selector(SceneFlyGame::addBlock), 0.5f);
	schedule(schedule_selector(SceneFlyGame::moveBlock));
	return true;
}

void SceneFlyGame::moveBlock(float)
{
	for (auto it = m_blocks.begin(); it != m_blocks.end(); )
	{
		Node * node = *it;
		node->setPositionX(node->getPositionX() - 4);
		if (node->getPositionX() < -node->getBoundingBox().size.width)
		{
			it = m_blocks.erase(it);
			node->removeFromParent();
		}
		else
		{
			++it;
		}
	}
}

void SceneFlyGame::addBlock(float)
{
	int r = CCRANDOM_0_1() * 5;
	if (r == 0)
	{
		// 加砖头
		r = CCRANDOM_0_1() * 6 + 4;
		Size size = Size(16, 16 * r);
		Node * node = Node::create();
		addChild(node);
		node->setContentSize(size);
		for (int i = 0; i < r; ++i)
		{
			Sprite * sprite = Sprite::create("superMarioMap.png", Rect(1, 1, 16, 16));
			node->addChild(sprite);
			sprite->setPosition(0, i * 16);
			sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		}
		node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		PhysicsBody * body = PhysicsBody::createEdgeBox(size);
		node->setPhysicsBody(body);
		body->setContactTestBitmask(1);
		// 设置node的位置
		r = CCRANDOM_0_1() * 2;	
		node->setPositionX(winSize.width + 16);
		if (r == 0)
			node->setPositionY(size.height / 2);
		else
			node->setPositionY(winSize.height - size.height / 2);
		// 加入数组
		m_blocks.pushBack(node);
	}
}

void SceneFlyGame::fly(float)
{
	if (m_dead) return;
	if (m_press)
	{
		Vec2 v = m_bird->getPhysicsBody()->getVelocity();
		m_bird->getPhysicsBody()->setVelocity(v + Vec2(0, 5));
		//Vec2 g = getPhysicsWorld()->getGravity();
		//g.y = -g.y;
		//getPhysicsWorld()->setGravity(g);
	}
}