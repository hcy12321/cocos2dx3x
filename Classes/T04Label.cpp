#include "T04Label.h"


bool T04Label::init()
{
	Layer::init();
	{
		Label * label = Label::createWithCharMap("fonts/Labelatlas.png", 24, 32, '0');
		label->setString("12345");
		addChild(label);
		label->setPosition(winSize.width / 2, winSize.height / 2);
	}
	/*
	Label * label = Label::createWithBMFont();
	Label * label = Label::createWithSystemFont("aaa", " Arial", 24);
	Label * label = Label::createWithTTF("");
	//Label * label = Label::createWithTexture();
	*/

	return true;
}
