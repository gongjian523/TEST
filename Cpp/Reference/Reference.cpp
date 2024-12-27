// Reference.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int var = 10;

//非引用返回的函数返回的都是右值，引用返回的函数返回的是左值
int fun1() { return var; };
int& fun2() { return var; };

int main()
{
	{
		//左值引用
		int a = 10;
		int& a1 = a;//正确，a为左值类型，因为可以我们找到他的地址
		//int& a = 10;//错误,左值引用不能引用一个右值类型的常量，（10是常量，常量为右值）

		int num = 10;
		const int& b = num;
		const int& c = 10; 
	}

	{
		//右值引用
		int&& a = 10;//正确，右值引用一个右值类型
		a = 100;
		std::cout << a << std::endl;//100


		//int&& var1 = var;//错误，因为无法将右值引用绑定到左值上
		//右值引用绝对不能引用左值类型的，加上const也不行，这点是和左值引用不同的地方
		//const int&& var1 = var//照样报错，加上const也不行

		//int& z = fun1();//左值引用，报错
		const int& z1 = fun1();//正确
		int&& z2 = fun1();//正确

		int& z = fun2();//左值引用，正确
		const int& z3= fun2();//延长生命期的左值引用，正确
		//int&& z2 = fun2();//报错，右值引用不能绑定左值
		//const int&& z2 = fun2();//报错
	}

	getchar();
}


