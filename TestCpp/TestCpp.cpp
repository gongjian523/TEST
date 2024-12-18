// TestCpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <regex>

#include "base.h"

#include <sstream>
#include <fstream>
#include <string>

#include "general.h"
#include "Timer.h"
#include "StringTest.h"
#include "QueueTest.h"
#include "RegexTest.h"
#include "Asio.h"
#include "TemplateTest.h"
#include "ProcessTest.h"

#include "testPoly.h"
#include "testErrorNoUI.h"

void splitAdd(std::string addr)
{
	std::string strLink;
	std::string strType; //typq beer1_broadcast

	char* p = (char*)addr.c_str();
	int nSize = strlen(p);

	std::regex re(",");
	std::cregex_token_iterator it(p, p + strlen(p), re, -1);
	std::cregex_token_iterator end;

	if (it != end)
	{
		strLink = *it++;
	}

	if (it != end)
	{
		strType = *it++;
	}

	if (strType.empty())
		std::cout << strLink << "\n";
	else
		std::cout << strLink << ":" << strType << "\n";

}


void ReadFileByLine(std::string path)
{
	unsigned char buf[44];
	std::ifstream in(path);
	std::string line;


	while (getline(in, line)) {//将in文件中的每一行字符读入到string line中
		std::stringstream ss(line);//使用string初始化stringstream

		int pos = 0;
		if ((pos = line.find("收到PIS应答：")) > 0)
		{
			memset(buf, 0x00, 44);

			int n = std::string("收到PIS应答：").size();

			std::string szData = line.substr(pos + n);

			char* p = (char*)szData.c_str();
			int nSize = strlen(p);

			std::regex re(" ");
			std::cregex_token_iterator it(p, p + strlen(p), re, -1);
			std::cregex_token_iterator end;

			for (int i = 0; i < 44; i++)
			{
				std::string szSigData = *it++;
				char* str;

				buf[i] = std::strtol(szSigData.c_str(), &str, 16);

				if (it == end)
					break;
			}

			std::shared_ptr<char> szInfo = std::shared_ptr<char>(new char[44 * 5], [](char* p) { delete[] p; });  //此对象析构时自动释放
			//for (size_t i = 0; i < 44; i++)
			//	sprintf(&szInfo.get()[i * 3], "%02x ", (unsigned char)buf[i]);

			std::cout << szInfo << std::endl;
		}
	}
}

void OnTimedEvent1()
{
	printf("\r\nTimer 1  Called");
}

void TestTimer()
{
	CTimer timer;

	timer.SetTimedEvent(OnTimedEvent1);
	timer.Start(5000, false, true);

	getchar();

	timer.Stop();
}

int main()
{
	//std::string addr3 = "192.168.17.47:6000,type";
	//splitAdd(addr3);
	//
	//std::string addr1 = "192.168.17.47:6000,";
	//splitAdd(addr1);

	//std::string addr2 = "192.168.17.47:6000, ";
	//splitAdd(addr2);

	//std::vector <Base *> m_basesVector;
	//m_basesVector.push_back(new Base());
	//m_basesVector.push_back(new Base());
	//m_basesVector.push_back(new Base());
	//m_basesVector.push_back(new Base());

	//std::vector <Base*>::iterator deleteIterator = m_basesVector.begin();
	//while (deleteIterator != m_basesVector.end()) {
	//	delete *deleteIterator;
	//	deleteIterator = m_basesVector.erase(deleteIterator);
	//}

	//m_basesVector.clear();


	//ReadFileByLine("D:\\项目资料\\弓网采集软件-06-长沙地铁3号线\\211125\\6364\\6364\\63\\Program_2021-11-18_09-45-54.7.log");

	//std::string szTempFilePath = "E:\\3C数据采集\\20211204\\000001_太原地铁2号线_未知";
	//std::string szScrPrefix = "E:\\3C数据采集";
	//std::string szDesPrefix = "G:";
	//
	//if (szScrPrefix != "" && szDesPrefix != "")
	//{
	//	std::string::size_type pos = szTempFilePath.find_first_of(szScrPrefix);

	//	if (pos != std::string::npos)
	//	{
	//		szTempFilePath.replace(pos, szScrPrefix.length(), szDesPrefix);
	//	}
	//}

	//GeneralTest();

	//TestTimer();

	//StringTest();

	//QueueCopy();

	//TestPoly::testPoly();

	//testErrorNoUI();

	//RegexTest();

	//TestAsio();

	//TemplateTest();

	//ProcessTest();
	//std::string sz = "2720011";

	//int ikilo = 2720011;

	//long long i1000 = ((long long)ikilo) * 1000;

	//int kilo = i1000 / 1000;

	//int iKiloMeter = (int)(kilo / 1000);
	//int iMeter = (int)(kilo % 1000);

	//int a = sizeof(int);
	//int b = sizeof(long);
	//int c = sizeof(long long);
	//int d = sizeof(short);
	//
	//float a1[100]{};
	//float* p = a1;
	//int b1= sizeof(*p);


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
