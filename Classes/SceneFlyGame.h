#ifndef __SCENEFLYGAME_H__
#define __SCENEFLYGAME_H__

#include "TCommon.h"

class SceneFlyGame : public Scene
{
public:
	CREATE_FUNC(SceneFlyGame);
	bool init();
	void fly(float);
	void addBlock(float);
	void moveBlock(float);

	bool m_press;
	bool m_dead;
	Vector<Node *> m_blocks;
	Sprite * m_bird;

};


#endif // !__SCENEFLYGAME_H__
