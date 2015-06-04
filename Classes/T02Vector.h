#ifndef __T02VECTOR_H__
#define __T02VECTOR_H__

#include "TCommon.h"

class T02Vector:public Layer
{
public:
	CREATE_FUNC(T02Vector);
	bool init();

	Vector<Sprite*> m_v;

};
#endif // !__T02VECTOR_H__



