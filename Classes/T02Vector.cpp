#include "T02Vector.h"


// 3.x Vector����CCArray
// �������Ref�����࣬�ǲ�����Vector��Ӧ����std::vector
bool T02Vector::init()
{
	Layer::init();
	Sprite * sprite = Sprite::create();
	// ����Ԫ��
	m_v.pushBack(sprite);

	// ����
	Vector<Sprite*>::iterator it;
	for (it = m_v.begin(); it != m_v.end(); ++it)
	{
		Sprite * s = *it;
	}

	for (auto it = m_v.begin(); it != m_v.end(); ++it)
	{

	}

	// �Ӻ���ǰɾ��
	for (auto it = m_v.rbegin(); it != m_v.rend(); ++it)
	{

	}

	// ɾ��
	m_v.eraseObject(sprite);

	return true;
}