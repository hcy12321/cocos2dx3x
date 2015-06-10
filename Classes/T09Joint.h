#ifndef __T09JOINT_H_
#define __T09JOINT_H_

#include "TCommon.h"

class T09Joint:public Layer
{
public:
	CREATE_FUNC(T09Joint);
	bool init();
	void onEnter();
	PhysicsWorld * getPhysicsWorld()
	{
		return ((Scene *)getParent())->getPhysicsWorld();
	}

	Sprite * m_A;
	Sprite * m_B;
	Sprite * m_C;
};


#endif // !__T09JOINT_H_
