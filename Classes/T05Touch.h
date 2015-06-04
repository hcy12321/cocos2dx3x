#ifndef __T05TOUCH_H__
#define __T05TOUCH_H__

#include "TCommon.h"

class T05Touch :public Layer
{
public:
	CREATE_FUNC(T05Touch);
	bool init();
	void TouchEnded(Touch *, Event *);
};


#endif // !__T05TOUCH_H__
