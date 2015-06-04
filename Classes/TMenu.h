#ifndef __TMENU_H__
#define __TMENU_H__

#include "TCommon.h"
class TMenu:public Layer
{
public:
	CREATE_FUNC(TMenu);
	bool init();
	bool touchBegan(Touch *, Event *);
};



#endif // !__TMENU_H__
