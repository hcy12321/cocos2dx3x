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
	// 最简单的lambada表达式是只要一个中括号和一个大括号
	// [] 捕获列表
	// {} 函数体
	// 1. 捕获列表，可以放变量名
	{
		int v = 100;
		auto func = [v]{return v; };
		int x = func();
	}
	// 2. 捕获列表，可以捕获多个变量
	{
		int p = 100, q = 200;
		auto func = [p, q]{return p + q; };
		int s = func();
	}
	// 3. 捕获列表，有引用和传值两种方式,传值不可以改变，引用可以改变，并且改变外部的变量值
	{
		int p = 100, q = 200;
		auto func = [p, &q]{
			q++; 
			//p++; // 报错
			return p + q;
		};
	}
	// 4. 捕获列表，可以定义mutable类型的lambada，能改变传值的捕获参数，但是不能改变外部的变量值
	{
		int p = 100, q = 200;
		auto func = [p, q]()mutable{p++; q++; return p + q; };
		int s = func();
		CCLog("p=%d,q=%d,s=%d", p, q, s);
	}
	// 5. 捕获列表，可以用=或者&捕获所有变量，=指传值，&表示引用
	{
		int p = 100, q = 200;
		auto func = [&]{
			this->setPosition(200, 100);
			return p + q;
		};
		// 除了q全部引用
		auto func1 = [&,q]{
			this->setPosition(200, 100);
			return p + q;
		};
		// 除了q全不引用
		auto func2 = [=, &q]
		{
			this->setPosition(200, 100);
			return p + q;
		};
	}

	// 稍微复杂点的lambada表达式
	{
		auto add = [](int v1, int v2){return v1 + v2; };
		auto a = add(1, 2);
	}
	// 小括号中的是参数列表，参数列表和捕获列表区别在于，参数列表的参数由调用放决定，捕获列表由定义放决定，这样更加灵活

	// 更加复杂的lambada表达式, 有返回值，返回值一般都省略
	{
		auto add = [](int v1, int v2)->int {return v1 + v2; };
	}

	// 总结 auto func = [](){};
	{
		auto func = [](){};
	}

	//////////////////////////////////////////////////////////////////////////
	{
		//std::function
		//std::bind
		/*
		// C 函数指针
		typedef void(*foo_type)();
		foo_type foo_ptr1;
		foo_ptr1 = foo;

		void(*foo_ptr)() = foo;
		// 100其情况
		// 动态绑定
		foo_type func[100] = { call1, call2 };
		func[status]();


		// 静态绑定
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


		// 函数指针类型

		std::function<void()> func = foo;
		func();
		// 成员函数指针的赋值和调用
		{
			void(T01CPP11::*funcPtr)() = &T01CPP11::mfoo;
			(this->*funcPtr)();
		}

		// bind功能，把一个具体函数，变成std::function对象
		// bind 可以把具体函数和std::function, 比如参数数量的改变
		{
			std::function<void()> func = std::bind(funArg3, 100, 'c',0.1f);
			func();
		}
		// 也可以改变参数顺序
		{
			std::function<void(float, char, int)> func = 
				std::bind(funArg3, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
			func(1.0f, 'd', 2000);
		}
		// 同时改变参数个数和顺序
		{
			std::function<void(float, char)> func =
				std::bind(funArg3, 100, std::placeholders::_2, std::placeholders::_1);
			func(4.0f, 'd');
		}
		// 也可以绑定成员函数
		{
			std::function<void()> func = std::bind(&T01CPP11::mfoo, this);
			func();
		}
		// 绑定lambada表达式
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