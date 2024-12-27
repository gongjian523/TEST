// TestDLL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "DLL.h"


typedef DLL* (pGetInstProc)();
typedef void (pFreeInstProc)();


int main()
{
    std::cout << "Input Dll number:" << std::endl;
    char  chInput = getchar();
    std::cout << "Dll" << chInput << " is chosed." << std::endl;

    char szDllName[32];
    memset(szDllName, 0, sizeof(szDllName));
    sprintf_s(szDllName, "DLL%c.dll", chInput);
    std::string strDllName(szDllName);

    WCHAR wszDllName[128];
    memset(wszDllName, 0, sizeof(wszDllName));

    MultiByteToWideChar(CP_ACP, 0, szDllName, strlen(szDllName) + 1, wszDllName,
        sizeof(wszDllName) / sizeof(wszDllName[0]));

    pGetInstProc* GetInst = nullptr;
    pFreeInstProc* FreeInst = nullptr;
    DLL* pDLL = nullptr;

    HINSTANCE hDll = LoadLibrary(wszDllName);
    if (hDll == nullptr) {
        std::cout << "Load " + strDllName + " failed!" << std::endl;
        goto lz_exit;
    }

    GetInst = (pGetInstProc*)GetProcAddress(hDll, "GetInst");
    if (GetInst == nullptr){
        std::cout << "Load GetInst failed!" << std::endl;
        goto lz_exit;
    }

    pDLL = GetInst();
    if (GetInst == nullptr) {
        std::cout << "GetInst failed!" << std::endl;
        goto lz_exit;
    }

    pDLL->Process();

    FreeInst = (pFreeInstProc*)GetProcAddress(hDll, "FreeInst");
    if (FreeInst == nullptr) {
        std::cout << "Load FreeInst failed!" << std::endl;
        goto lz_exit;
    }

    FreeInst();

lz_exit:
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
