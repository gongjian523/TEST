// RAII.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <mutex>

namespace TestUnit1
{
    template<class PointerType>
    class My_Pointer
    {
    public:
        My_Pointer(PointerType* _ptr, size_t sz)
        {
            _ptr = new PointerType[sz];
            m_ptr = _ptr;
        }
        ~My_Pointer()
        {
            std::cout << "rel" << std::endl;
            delete []m_ptr;
        }
    protected:
        PointerType*    m_ptr;
    };

    void Test()
    {
        int* ptr;
        My_Pointer<int*> obj(&ptr,10);

        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }

        for (int i = 0; i < 10; i++) {
            std::cout << ptr[i] << std::endl;
        }
    }
}

namespace TestUnit2 {
    template<class LockType>
    class My_scope_lock
    {
    public:
        My_scope_lock(LockType& _lock) :m_lock(_lock)
        {
            m_lock.occupy();
        }
        ~My_scope_lock()
        {
            m_lock.relase();
        }
    protected:
        LockType    m_lock;
    };



}


int main()
{
    TestUnit1::Test();
    getchar();
}

