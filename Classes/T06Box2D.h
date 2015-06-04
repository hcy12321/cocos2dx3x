#ifndef __T06BOX2D_H__
#define __T06BOX2D_H__

#include "TCommon.h"
#include "Box2D/Box2D.h"

class T06Box2D:public Layer
{
public:
	CREATE_FUNC(T06Box2D);
	bool init();
	void update(float dt);

	b2World * m_world;
	b2Body * m_bat;
};


#endif // !__T06BOX2D_H__
