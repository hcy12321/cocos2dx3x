#include "T03Map.h"

// ValueMap 代替cocos2.x中的CCDictinary
bool T03Map::init()
{
	Layer::init();

	ValueMap& vm = FileUtils::getInstance()->getValueMapFromFile("about.xml");
	//CCDictionary * dict = CCDictionary::createWithContentsOfFile("about.xml");
	// 查找
	auto it = vm.find("aaa");
	if (it == vm.end())
	{
		// 没找到
		CCLog("can not find aaa");
	}

	it = vm.find("people3");
	it->first; // key 类型std::string
	it->second; // value 类型Value相对于cocos2dx 2.x的CCString

	CCLog("key is %s, value is %s", it->first.c_str(), it->second.asString().c_str());

	it->first.c_str();
	Value v = it->second;
	v.asInt();
	v.asString();
	v.asBool();

	vm["people6"] = "hh";

	// 遍历
	CCLog("start walk over");
	for (auto it = vm.begin(); it != vm.end();++it)
	{
		CCLog("key is %s, value is %s", it->first.c_str(), it->second.asString().c_str());
	}
	CCLog("end");
	FileUtils::getInstance()->writeToFile(vm, "new.xml");
	// 范围for C++ 11
	for (auto it : vm)
	{
		it.first;
		it.second;
	}
	/*
	// 插入
	vm["aa"] = 10; // 有则插入，没有则改变

	// 访问，有副作用，如果节点不存在，ta会创建一个节点
	//Value &v = vm["aa"];
	//v = 100;
	*/
	return true;
}