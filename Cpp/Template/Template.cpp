// Template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

namespace TestUnit1 {


const int size = 100;

template <class T>
class Array {

private:
	int l, z;
	T array[size];

public:
	Array(T* b, int n);

	void Sort();

	void Reverse();

	bool Find(T b);

	T Sum();
};

template <class T>
Array<T>::Array(T* b, int n) {

}

template <class T>
void Array<T>::Sort()
{

}

template <class T>
void Array<T>::Reverse()
{

}

template <class T>
bool Array<T>::Find(T b)
{
	
}

template <class T>
T Array<T>::Sum()
{

}


}


namespace TestUnit2 {
	class Person1
	{
	public:
		void showPerson1()
		{
			std::cout << "Person1 show" << std::endl;
		}
	};

	class Person2
	{
	public:
		void showPerson2()
		{
			std::cout << "Person2 show" << std::endl;
		}
	};

	template<class T>
	class MyClass
	{
	public:
		T obj;

		//类模板中的成员函数，并不是一开始就创建的，而是在模板调用时再生成

		void fun1() { obj.showPerson1(); }
		void fun2() { obj.showPerson2(); }

	};

	int Test() {

		MyClass<Person1> m;
		m.fun1();
		//m.fun2();//编译会出错，说明函数调用才会去创建成员函数
		
		return 0;
	}
}


namespace TestUnit3 {


	//类模板
	template<class NameType, class AgeType = int>
	class Person
	{
	public:
		Person(NameType name, AgeType age)
		{
			this->mName = name;
			this->mAge = age;
		}
		void showPerson()
		{
			std::cout << "name: " << this->mName << " age: " << this->mAge << std::endl;
		}
	public:
		NameType mName;
		AgeType mAge;
	};

	//1、指定传入的类型
	void printPerson1(Person<std::string, int>& p)
	{
		p.showPerson();
	}
	void test01()
	{
		Person <std::string, int >p("孙悟空", 100);
		printPerson1(p);
	}

	//2、参数模板化
	template <class T1, class T2>
	void printPerson2(Person<T1, T2>& p)
	{
		p.showPerson();
		std::cout << "T1的类型为： " << typeid(T1).name() << std::endl;
		std::cout << "T2的类型为： " << typeid(T2).name() << std::endl;
	}
	void test02()
	{
		Person <std::string, int >p("猪八戒", 90);
		printPerson2(p);
	}

	//3、整个类模板化
	template<class T>
	void printPerson3(T& p)
	{
		std::cout << "T的类型为： " << typeid(T).name() << std::endl;
		p.showPerson();

	}
	void test03()
	{
		Person <std::string, int >p("唐僧", 30);
		printPerson3(p);
	}

	int Test() {

		test01();
		test02();
		test03();

		return 0;
	}
}


namespace TestUnit4 {
	template<class T>
	class Base
	{
		T m;
	};

	//class Son:public Base  //错误，c++编译需要给子类分配内存，必须知道父类中T的类型才可以向下继承
	class Son :public Base<int> //必须指定一个类型
	{
	};
	void test01()
	{
		Son c;
	}

	//类模板继承类模板 ,可以用T2指定父类中的T类型
	template<class T1,class T2>
	class Son2 :public Base<T1>
	{
	public:
		Son2()
		{
			std::cout << typeid(T1).name() << std::endl;
			std::cout << typeid(T2).name() << std::endl;
		}
	};

	void test02()
	{
		Son2<int,char> child1;
	}


	int Test() {

		test01();

		test02();

		return 0;
	}
}

#include "Person.hpp"

namespace TestUnit5
{
	int Test()
	{
		Person<std::string, int> p("Tom", 10);
		p.showPerson();
		return 0;
	}
}

namespace TestUnit6
{
#include <string>

	//2、全局函数配合友元  类外实现 - 先做函数模板声明，下方在做函数模板定义，在做友元
	template<class T1, class T2> class Person;

	//如果声明了函数模板，可以将实现写到后面，否则需要将实现体写到类的前面让编译器提前看到
	//template<class T1, class T2> void printPerson2(Person<T1, T2> & p); 
	
	template<class T1, class T2>
	void printPerson2(Person<T1, T2>& p)
	{
		std::cout << "类外实现 ---- 姓名： " << p.m_Name << " 年龄：" << p.m_Age << std::endl;
	}



	template<class T1, class T2>
	class Person
	{
		//1、全局函数配合友元   类内实现
		friend void printPerson(Person<T1, T2>& p)
		{
			std::cout << "姓名： " << p.m_Name << " 年龄：" << p.m_Age << std::endl;
		}


		//全局函数配合友元  类外实现
		friend void printPerson2<>(Person<T1, T2>& p);

	public:

		Person(T1 name, T2 age)
		{
			this->m_Name = name;
			this->m_Age = age;
		}


	private:
		T1 m_Name;
		T2 m_Age;

	};



	//1、全局函数在类内实现
	void test01()
	{
		Person <std::string, int >p("Tom", 20);
		printPerson(p);
	}


	//2、全局函数在类外实现
	void test02()
	{
		Person <std::string, int >p("Jerry", 30);
		printPerson2(p);
	}

	int Test() {

		test01();

		test02();

		return 0;
	}


}

int main()
{
	//TestUnit2::Test();
	//TestUnit3::Test();
	//TestUnit4::Test();
	//TestUnit5::Test();
	TestUnit6::Test();
	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
