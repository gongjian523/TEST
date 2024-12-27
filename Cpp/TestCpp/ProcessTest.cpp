#include "ProcessTest.h"
#include <algorithm>
#include <iostream>
#include "Windows.h"
#include "tlhelp32.h"



void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText; 
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}


bool KillPorcess()
{

	const char* strProcessName = "1.exe";

	//创建进程快照(TH32CS_SNAPPROCESS表示创建所有进程的快照) 
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//PROCESSENTRY32进程快照的结构体 
	PROCESSENTRY32 pe;
	//实例化后使用Process32First获取第一个快照的进程前必做的初始化操作 
	pe.dwSize = sizeof(PROCESSENTRY32);

	//下面的IF效果同: 
	//if(hProcessSnap == INVALID_HANDLE_VALUE) 无效的句柄 
	if (!Process32First(hSnapShot, &pe))
	{
		return FALSE;
	}

	//将字符串转换为小写 
	std::string strProcessNameLower = strProcessName;
	std::transform(strProcessNameLower.begin(), strProcessNameLower.end(), strProcessNameLower.begin(), ::tolower);

	//如果句柄有效 则一直获取下一个句柄循环下去 
	while (Process32Next(hSnapShot, &pe))
	{
		//pe.szExeFile获取当前进程的可执行文件名称 
		std::string strExeFile;
			
		Wchar_tToString(strExeFile, const_cast<wchar_t*>(pe.szExeFile));
		std::transform(strExeFile.begin(), strExeFile.end(), strExeFile.begin(), ::tolower);

		//比较当前进程的可执行文件名称和传递进来的文件名称是否相同 
		//相同的话strcmp返回0 
		if (strcmp(strProcessNameLower.c_str(), strExeFile.c_str()) == 0)
		{
			//从快照进程中获取该进程的PID(即任务管理器中的PID) 
			DWORD dwProcessID = pe.th32ProcessID;
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
			::TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
			return TRUE;
		}
	}
	return FALSE;
}


void ProcessTest()
{
	KillPorcess();
}