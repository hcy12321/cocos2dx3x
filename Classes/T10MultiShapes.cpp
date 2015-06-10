#include "T10MultiShapes.h"

bool T10MultiShapes::init()
{
	Layer::init();
	{
		PhysicsBody * body = PhysicsBody::create();
		PhysicsShape * shape1 = PhysicsShapeBox::create(Size(40, 40), PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
		body->addShape(shape1);

		PhysicsShape * shape2 = PhysicsShapeCircle::create(10, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(-30, 0));
		body->addShape(shape2);

		Node * node = Node::create();
		node->setPhysicsBody(body);

		addChild(node);
		node->setPosition(winSize.width / 2, winSize.height / 2);
	}
	{
		PhysicsBody * body = PhysicsBody::createEdgeBox(winSize, PhysicsMaterial(1.0f, 1.0f, 1.0f));
		Sprite * sprite = Sprite::create();
		addChild(sprite);
		sprite->setPhysicsBody(body);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);
	}
	return true;
}