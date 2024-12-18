// TestDLL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "../Dll1/DLL1.h"
#include "../Dll2/DLL2.h"


int main()
{
    HINSTANCE hDll1 = LoadLibrary(L"D:\\Worksapce\\Test\\x64\\Debug\\DLL\\DLL1.dll");
    if (hDll1 == nullptr) {
        std::cout << "Load DLL1 failed !"<< "\n";
    }
    HINSTANCE hDll2 = LoadLibrary(L"D:\\Worksapce\\Test\\x64\\Debug\\DLL\\DLL2.dll");
    if (hDll2 == nullptr) {
        std::cout << "Load DLL2 failed !" << "\n";
    }

    std::cout << "Input Dll num:!\n";
    char  chInpt = getchar();

    DLL1* pDll1 = nullptr;
    DLL2* pDll2 = nullptr;

    if (chInpt == '1') {
        std::cout << "Choose Dll 1!\n";

        pDll1 = new DLL1();
        
        if (pDll1 != nullptr) {
            //pDll1->Process();
            delete pDll1;
        }
    }
    else if (chInpt == '2') {
        std::cout << "Choose Dll 2!\n";

        pDll2 = new DLL2();

        if (pDll2 != nullptr) {
            pDll2->Process();
            delete pDll2;
        }
    }
    else {
        std::cout << "Choose Dll !" << chInpt << "\n";
    }

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
