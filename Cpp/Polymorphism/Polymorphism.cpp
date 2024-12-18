// Polymorphism.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#include <string>
#include <iostream>
#include <list>


#ifdef WIN32
#define funcPtr (int *)
#define funcPtr1 int *
#else
#define funcPtr (long long *)
#define funcPtr1 long long *
#endif

namespace TestUnit1
{
    class Person
    {
    public:
        Person() {}; //成员列表初始化参数  
        virtual ~Person() {};
        virtual void  GetName() = 0;//获取名字  
        virtual void GetNationality() = 0;//获取名字  
    protected:
        std::string m_StrName;
        std::string m_StrNationality;
    };

    class Father : public Person
    {
    public:
        Father() {};
        ~Father() {};
        virtual void GetName() {
            std::cout << "Father's name is Json" << std::endl;
        };
        void GetNationality() {
            std::cout << "Father's Nationality is chinese" << std::endl;
        }
    };

    class Son : public Father
    {
    public:
        Son() {};
        ~Son() {};
        void GetName() {
            std::cout << "Son's name is Mike" << std::endl;
        };
    };

    std::list<Father*> list;
    std::list<Father*>::iterator iter;

    void Test()
    {
        Father* p1 = new Father();
        Son* p2 = new Son();

        list.push_back(p1);
        list.push_back(p2);

        for (iter = list.begin(); iter != list.end(); iter++)
        {
            (*iter)->GetName();
            (*iter)->GetNationality();
        }
    }
}

namespace TestUnit2
{
    class Father2
    {
    public:
        void Face()
        {
            std::cout << "Father's face" << std::endl;
        }

        void Say()
        {
            std::cout << "Father say hello" << std::endl;
        }
    };

    class Son2 :public Father2
    {
    public:
        virtual void Say()
        {
            std::cout << "Son say hello" << std::endl;
        }
    };

    class GrandSon2 :public Son2
    {
    public:
        void Say()
        {
            std::cout << "GrandSon say hello" << std::endl;
        }
    };

    void Test()
    {
        GrandSon2 grandSon2;
        Father2* pFather = &grandSon2; // 隐式类型转换
        pFather->Say();

        Son2* pSon = &grandSon2;
        pSon->Say();
    }
}

namespace TestUnit3
{
    class CA
    {
    public:
        void f()
        {
            std::cout << "CA f()" << std::endl;
        }
        virtual void ff()
        {
            std::cout << "CA ff()" << std::endl;
            f();
        }
    };

    class CB : public CA
    {
    public:
        virtual void f()
        {
            std::cout << "CB f()" << std::endl;
        }
        void ff()
        {
            std::cout << "CB ff()" << std::endl;
            f();
            CA::ff();
        }
    };
    class CC : public CB
    {
    public:
        virtual void f()
        {
            std::cout << "C f()" << std::endl;
        }
    };

    void Test()
    {
        CB b;
        CA* ap = &b;
        CC c;
        CB& br = c;
        CB* bp = &c;

        ap->f();
        std::cout << std::endl;

        b.f();
        std::cout << std::endl;

        br.f();
        std::cout << std::endl;

        bp->f();
        std::cout << std::endl;

        ap->ff();
        std::cout << std::endl;

        bp->ff();
        std::cout << std::endl;

    }

}

namespace TestUnit4
{
    class Base {
    public:
        virtual void f() { std::cout << "Base::f" << std::endl; }
        virtual void g() { std::cout << "Base::g" << std::endl; }
        virtual void h() { std::cout << "Base::h" << std::endl; }

    };


    class Devired :public Base {
    public:
        virtual void x() { std::cout << "x()" << std::endl; }
        virtual void f() { std::cout << "Devired::f" << std::endl; }
    };


    typedef void(*Fun)(void);

    void Test()
    {
        Fun pFun = NULL;

        Base t;
        (((void(*)()) * (funcPtr(*(funcPtr & t)) + 0)))     ();
        (((void(*)()) * (funcPtr(*(funcPtr & t)) + 1)))     ();
        (((void(*)()) * (funcPtr(*(funcPtr & t)) + 2)))     ();


        Devired d;
        (((void(*)()) * (funcPtr(*(funcPtr & d)) + 0)))     ();
        (((void(*)()) * (funcPtr(*(funcPtr & d)) + 1)))     ();
        (((void(*)()) * (funcPtr(*(funcPtr & d)) + 2)))     ();
        (((void(*)()) * (funcPtr(*(funcPtr & d)) + 3)))     ();

        Base obj_1, obj_2;
        // obj_1 虚函数表 — 第一个函数
        pFun = (Fun) * ((funcPtr * funcPtr(&obj_1)) + 0);
        pFun();
        pFun = (Fun) * ((funcPtr * funcPtr(&obj_1)) + 1);
        pFun();
        pFun = (Fun) * ((funcPtr * funcPtr(&obj_1)) + 2);
        pFun();
        // 输出 虚函数表地址 与 虚函数表元素 的值
        std::cout << "obj_1 虚函数表地址：" << funcPtr(&obj_1) << std::endl;
        std::cout << "obj_2 虚函数表地址：" << funcPtr(&obj_2) << std::endl;
        std::cout << "obj_1 虚函数表 — 第一个函数地址：" << funcPtr * funcPtr(&obj_1) << std::endl;
        std::cout << "obj_2 虚函数表 — 第一个函数地址：" << funcPtr * funcPtr(&obj_2) << std::endl;
    }
}

namespace TestUnit5{

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

    void Test()
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

}


int main()
{
    TestUnit1::Test();
    TestUnit2::Test();
    TestUnit3::Test();
    TestUnit4::Test();
    TestUnit5::Test();

    getchar();
}

