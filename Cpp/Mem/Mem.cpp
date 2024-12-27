// Mem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#ifdef WIN32
#define funcPtr (int *)
#define funcPtr1 int *
#else
#define funcPtr (long long *)
#define funcPtr1 long long *
#endif

class Base1
{
public:
    Base1(int mem1 = 1, int mem2 = 2) : m_iMem1(mem1), m_iMem2(mem2) { ; }

    virtual void vfunc1() { std::cout << "In vfunc1()" << std::endl; }
    virtual void vfunc2() { std::cout << "In vfunc2()" << std::endl; }
    virtual void vfunc3() { std::cout << "In vfunc3()" << std::endl; }

private:
    int m_iMem1;
    int m_iMem2;
};

class Base2
{
public:
    Base2(int mem = 3) : m_iBase2Mem(mem) { ; }
    virtual void vBase2func1() { std::cout << "In Base2 vfunc1()" << std::endl; }
    virtual void vBase2func2() { std::cout << "In Base2 vfunc2()" << std::endl; }

private:
    int m_iBase2Mem;
};

class Base3
{
public:
    Base3(int mem = 4) : m_iBase3Mem(mem) { ; }
    virtual void vBase3func1() { std::cout << "In Base3 vfunc1()" << std::endl; }
    virtual void vBase3func2() { std::cout << "In Base3 vfunc2()" << std::endl; }

private:
    int m_iBase3Mem;
};

class Devired1 : public Base1, public Base2, public Base3
{
public:
    Devired1(int mem = 7) : m_iMem1(mem) { ; }
    virtual void vdfunc1() { std::cout << "In Devired vdfunc1()" << std::endl; }
    virtual void vfunc1() { std::cout << "In Devired vfunc1()" << std::endl; }
    virtual void vBase2func1() { std::cout << "In Devired vBase2func1()" << std::endl; }
private:
    int m_iMem1;
};


typedef void(*FUNC)();

void testPoly5()
{
    Devired1 d;
    int* dAddress = (int*)&d;

    Base1* pBase1 = (Base1*)&d;

    std::cout << sizeof(FUNC) << std::endl;

    /* 1. 获取对象的内存布局信息 */
    // 虚表地址一
    funcPtr1 vtptr1 = (funcPtr1) * (dAddress + 0);
    int basemem1 = (int)*(dAddress + 1);
    int basemem2 = (int)*(dAddress + 2);

    funcPtr1 vtpttr2 = (funcPtr1) * (dAddress + 3);
    int base2mem = (int)*(dAddress + 4);

    funcPtr1 vtptr3 = (funcPtr1) * (dAddress + 5);
    int base3mem = (int)*(dAddress + 6);


    /* 2. 输出对象的内存布局信息 */
    funcPtr1 pBaseFunc1 = (funcPtr1) * (vtptr1 + 0);
    funcPtr1 pBaseFunc2 = (funcPtr1) * (vtptr1 + 1);
    funcPtr1 pBaseFunc3 = (funcPtr1) * (vtptr1 + 2);
    funcPtr1 pBaseFunc8 = (funcPtr1) * (vtptr1 + 3);
    funcPtr1 pBaseFunc4 = (funcPtr1) * (vtpttr2 + 0);
    funcPtr1 pBaseFunc5 = (funcPtr1) * (vtpttr2 + 1);
    funcPtr1 pBaseFunc6 = (funcPtr1) * (vtptr3 + 0);
    funcPtr1 pBaseFunc7 = (funcPtr1) * (vtptr3 + 1);

    (FUNC(pBaseFunc1))();
    (FUNC(pBaseFunc2))();
    (FUNC(pBaseFunc3))();
    (FUNC(pBaseFunc8))();
    (FUNC(pBaseFunc4))();
    (FUNC(pBaseFunc5))();
    (FUNC(pBaseFunc6))();
    (FUNC(pBaseFunc7))();

    Base1 b;
    int* bAddress = (int*)&b;

    vtptr1 = (funcPtr1) * (bAddress + 0);
    pBaseFunc1 = (funcPtr1) * (vtptr1 + 0);
    pBaseFunc2 = (funcPtr1) * (vtptr1 + 1);
    (FUNC(pBaseFunc1))();
    (FUNC(pBaseFunc2))();
}

int main()
{
    testPoly5();
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
