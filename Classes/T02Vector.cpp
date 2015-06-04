#include "T02Vector.h"


// 3.x Vector代替CCArray
// 如果不是Ref的子类，那不能用Vector，应该用std::vector
bool T02Vector::init()
{
	Layer::init();
	Sprite * sprite = Sprite::create();
	// 增加元素
	m_v.pushBack(sprite);

	// 遍历
	Vector<Sprite*>::iterator it;
	for (it = m_v.begin(); it != m_v.end(); ++it)
	{
		Sprite * s = *it;
	}

	for (auto it = m_v.begin(); it != m_v.end(); ++it)
	{

	}

	// 从后往前删除
	for (auto it = m_v.rbegin(); it != m_v.rend(); ++it)
	{

	}

	// 删除
	m_v.eraseObject(sprite);

	return true;
}