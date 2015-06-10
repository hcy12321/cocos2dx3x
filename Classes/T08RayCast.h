#ifndef __T08RAYCAST_H__
#define __T08RAYCAST_H__

#include "TCommon.h"

class T08RayCast:public Layer
{
public:
	CREATE_FUNC(T08RayCast);
	bool init();
	void onEnter();
	void update(float delta);

	Sprite * m_cat;
	int m_nangel;
	int m_ndistance;
	float m_fnearDis;
	PhysicsShape * m_food;
	DrawNode * m_drawNode;
};



#endif // !__T08RAYCAST_H__
