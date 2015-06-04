#include "T01CPP11.h"

void foo()
{
	CCLog("foo is called \n");
}

void funArg3(int n, char c, float f)
{
	CCLog("%d, %c,%f", n, c, f);
}

bool T01CPP11::init()
{
	Layer::init();

	// Lambada
	auto func = []{return 1; };
	int i = func();//[]{return 1; }();
	// ��򵥵�lambada���ʽ��ֻҪһ�������ź�һ��������
	// [] �����б�
	// {} ������
	// 1. �����б����Էű�����
	{
		int v = 100;
		auto func = [v]{return v; };
		int x = func();
	}
	// 2. �����б����Բ���������
	{
		int p = 100, q = 200;
		auto func = [p, q]{return p + q; };
		int s = func();
	}
	// 3. �����б������úʹ�ֵ���ַ�ʽ,��ֵ�����Ըı䣬���ÿ��Ըı䣬���Ҹı��ⲿ�ı���ֵ
	{
		int p = 100, q = 200;
		auto func = [p, &q]{
			q++; 
			//p++; // ����
			return p + q;
		};
	}
	// 4. �����б����Զ���mutable���͵�lambada���ܸı䴫ֵ�Ĳ�����������ǲ��ܸı��ⲿ�ı���ֵ
	{
		int p = 100, q = 200;
		auto func = [p, q]()mutable{p++; q++; return p + q; };
		int s = func();
		CCLog("p=%d,q=%d,s=%d", p, q, s);
	}
	// 5. �����б�������=����&�������б�����=ָ��ֵ��&��ʾ����
	{
		int p = 100, q = 200;
		auto func = [&]{
			this->setPosition(200, 100);
			return p + q;
		};
		// ����qȫ������
		auto func1 = [&,q]{
			this->setPosition(200, 100);
			return p + q;
		};
		// ����qȫ������
		auto func2 = [=, &q]
		{
			this->setPosition(200, 100);
			return p + q;
		};
	}

	// ��΢���ӵ��lambada���ʽ
	{
		auto add = [](int v1, int v2){return v1 + v2; };
		auto a = add(1, 2);
	}
	// С�����е��ǲ����б������б�Ͳ����б��������ڣ������б�Ĳ����ɵ��÷ž����������б��ɶ���ž����������������

	// ���Ӹ��ӵ�lambada���ʽ, �з���ֵ������ֵһ�㶼ʡ��
	{
		auto add = [](int v1, int v2)->int {return v1 + v2; };
	}

	// �ܽ� auto func = [](){};
	{
		auto func = [](){};
	}

	//////////////////////////////////////////////////////////////////////////
	{
		//std::function
		//std::bind
		/*
		// C ����ָ��
		typedef void(*foo_type)();
		foo_type foo_ptr1;
		foo_ptr1 = foo;

		void(*foo_ptr)() = foo;
		// 100�����
		// ��̬��
		foo_type func[100] = { call1, call2 };
		func[status]();


		// ��̬��
		switch (status)
		{
		case 1:
		call1();
		break;
		case 2:
		call2();
		break;
		}
		*/

	}
	{


		// ����ָ������

		std::function<void()> func = foo;
		func();
		// ��Ա����ָ��ĸ�ֵ�͵���
		{
			void(T01CPP11::*funcPtr)() = &T01CPP11::mfoo;
			(this->*funcPtr)();
		}

		// bind���ܣ���һ�����庯�������std::function����
		// bind ���԰Ѿ��庯����std::function, ������������ĸı�
		{
			std::function<void()> func = std::bind(funArg3, 100, 'c',0.1f);
			func();
		}
		// Ҳ���Ըı����˳��
		{
			std::function<void(float, char, int)> func = 
				std::bind(funArg3, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
			func(1.0f, 'd', 2000);
		}
		// ͬʱ�ı����������˳��
		{
			std::function<void(float, char)> func =
				std::bind(funArg3, 100, std::placeholders::_2, std::placeholders::_1);
			func(4.0f, 'd');
		}
		// Ҳ���԰󶨳�Ա����
		{
			std::function<void()> func = std::bind(&T01CPP11::mfoo, this);
			func();
		}
		// ��lambada���ʽ
		{
			std::function<void()> func = [](){};
			std::function<void(int)> func1 = std::bind([](int,int){
				CCLog("lambada is called");
			}, 10,std::placeholders::_1);
			func1(100);
		}
	}
	return true;
}

void T01CPP11::mfoo()
{
	CCLog("mFoo is called");
}