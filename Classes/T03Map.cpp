#include "T03Map.h"

// ValueMap ����cocos2.x�е�CCDictinary
bool T03Map::init()
{
	Layer::init();

	ValueMap& vm = FileUtils::getInstance()->getValueMapFromFile("about.xml");
	//CCDictionary * dict = CCDictionary::createWithContentsOfFile("about.xml");
	// ����
	auto it = vm.find("aaa");
	if (it == vm.end())
	{
		// û�ҵ�
		CCLog("can not find aaa");
	}

	it = vm.find("people3");
	it->first; // key ����std::string
	it->second; // value ����Value�����cocos2dx 2.x��CCString

	CCLog("key is %s, value is %s", it->first.c_str(), it->second.asString().c_str());

	it->first.c_str();
	Value v = it->second;
	v.asInt();
	v.asString();
	v.asBool();

	vm["people6"] = "hh";

	// ����
	CCLog("start walk over");
	for (auto it = vm.begin(); it != vm.end();++it)
	{
		CCLog("key is %s, value is %s", it->first.c_str(), it->second.asString().c_str());
	}
	CCLog("end");
	FileUtils::getInstance()->writeToFile(vm, "new.xml");
	// ��Χfor C++ 11
	for (auto it : vm)
	{
		it.first;
		it.second;
	}
	/*
	// ����
	vm["aa"] = 10; // ������룬û����ı�

	// ���ʣ��и����ã�����ڵ㲻���ڣ�ta�ᴴ��һ���ڵ�
	//Value &v = vm["aa"];
	//v = 100;
	*/
	return true;
}