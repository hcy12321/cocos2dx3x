#ifndef __T07PHYSICSWORLD__H_
#define __T07PHYSICSWORLD__H_

#include "TCommon.h"

class T07PhysicsWorld :public Layer
{
public:
	CREATE_FUNC(T07PhysicsWorld);
	bool init();

	Scene * getScene();
};


#endif // !__T07PHSICSWORLD__H_

