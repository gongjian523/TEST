// TestMuiltThreads.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "stdio.h"
#include "windows.h"
#include <iostream>
#include <thread>

using namespace std;

DWORD WINAPI FunProc(LPVOID lpParameter);

DWORD WINAPI FunProc(LPVOID lpParameter)
{
	for (int i = 0; i < 10; i++)
	{
		cout << "[thread1] " << i << endl;

		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI FunProc2(LPVOID lpParameter)
{
	for (int i = 0; i < 5; i++)
	{
		cout << "[thread2] " << i << endl;

		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI FunProc3(LPVOID lpParameter)
{
	for (int i = 0; i < 15; i++)
	{
		cout << "[thread3] " << i << endl;

		Sleep(1000);
	}
	return 0;
}

int main()
{
	//HANDLE hThread, hThread2;

	HANDLE hThread[3];

	hThread[0] = CreateThread(NULL, 0, FunProc, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, FunProc2, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, FunProc3, NULL, 0, NULL);
	
	DWORD dwRet;
	bool bExit = false;

	while(!bExit)
	{
		//cout << "[threadM] Waiting Thread" << endl;
		dwRet = WaitForMultipleObjects(3, hThread, false , 1000);

		cout << "[threadM] " << dwRet << endl;

		if ((dwRet - WAIT_OBJECT_0) == 0)
		{
			bExit = true;
			cout << "[threadM] Thread finished" << endl;
		}

		
		//switch (dwRet)
		//{
		//case WAIT_OBJECT_0:
		//	bExit = true;
		//	cout << "[threadM] Thread finished" << endl;
		//	break;
		//case WAIT_TIMEOUT:
		//	cout << "[threadM] Timeout" << endl;
		//	break;
		//case WAIT_ABANDONED:
		//	bExit = true;
		//	cout << "[threadM] Abandoned" << endl;
		//	break;
		//default:
		//	cout << "[threadM] " << dwRet << endl;
		//	break;
		//}
	}

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);


	system("pause");
	
	return 0;
}
