// ScanFilesCPP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <io.h>
#include <iostream>
#include <fstream>
#include <sstream> 

#include <boost/system/error_code.hpp> 
#include <boost/filesystem.hpp>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <memory>

#include "windows.h"


bool DateVerify(int year, int month, int day)
{
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		return false;
	}

	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		if (day > 30)
		{   // 4.6.9.11月天数不能大于30
			return false;
		}
		break;
	case 2:
	{
		bool bLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if ((bLeapYear && day > 29) || (!bLeapYear && day > 28))
		{
			// 闰年2月不能大于29天;平年2月不能大于28天
			return false;
		}
	}
	break;
	default:
		break;
	}

	return true;
}

bool CheckDateValid(const std::string strDate)
{
	if (strDate.length() != 8)
	{
		return false;
	}

	int nYear, nMonth, nDay;
	try {
		// TODO:这里最好再下判断字符转换是否成功
		nYear = atoi(strDate.substr(0, 4).c_str());
		nMonth = atoi(strDate.substr(4, 2).c_str());
		nDay = atoi(strDate.substr(6, 2).c_str());
	}
	catch (std::exception& e) {
		return false;
	}

	return DateVerify(nYear, nMonth, nDay);
}


bool CheckTimeValid(const std::string strDate)
{
	if (strDate.length() != 6)
	{
		return false;
	}

	int nHour, nMinute, nSecond;
	try {
		nHour = atoi(strDate.substr(0, 2).c_str());
		nMinute = atoi(strDate.substr(2, 2).c_str());
		nSecond = atoi(strDate.substr(4, 2).c_str());
	}
	catch (std::exception& e) {
		return false;
	}

	return (nHour >= 0 && nHour <= 23) && (nMinute >= 0 && nMinute <= 59) && (nSecond >= 0 && nSecond <= 59);
}


void WindowsScan()
{
	_finddata_t FileInfo;
	std::string strfind = "E:\\转辙机数据\\*";

	intptr_t handle = _findfirst(strfind.c_str(), &FileInfo);
	if (handle == -1L) {
		goto lz_exit;
	}

	do {
		//判断是否有子目录  
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//这个语句很重要  
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				std::string newPath = strfind + "\\" + FileInfo.name;

				std::cout << strfind.c_str() << "\\" << FileInfo.name << std::endl;
			}
		}
		else
		{
			std::cout << strfind.c_str() << "\\" << FileInfo.name << std::endl;
		}
	} while (_findnext(handle, &FileInfo) == 0);

	_findclose(handle);

lz_exit:
	return;
}

void BoostScan() 
{
	std::string targetPath = "E:\\转辙机数据\\";
	boost::filesystem::path myPath(targetPath);


	boost::filesystem::directory_iterator endIter;
	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
		if (boost::filesystem::is_directory(*iter)) {
			std::cout << "is dir" << std::endl;
			std::cout << iter->path().string() << std::endl;
		}
		else {
			std::cout << "is a file" << std::endl;
			std::cout << iter->path().string() << std::endl;
		}
	}

	boost::filesystem::recursive_directory_iterator recendIter;
	for (boost::filesystem::recursive_directory_iterator iter(myPath); iter != recendIter; iter++) {
		if (boost::filesystem::is_directory(*iter)) {
			std::cout << "is dir" << std::endl;
			std::cout << iter->path().string() << std::endl;
		}
		else {
			std::cout << "is a file" << std::endl;
			std::cout << iter->path().string() << std::endl;
		}
	}
}


bool IsFileExistent(const boost::filesystem::path& path) {

    boost::system::error_code error;
    auto file_status = boost::filesystem::status(path, error);
    if (error) {
        return false;
    }

    if (!boost::filesystem::exists(file_status)) {
        return false;
    }

    if (boost::filesystem::is_directory(file_status)) {
        return false;
    }

    return true;
}



int main()
{
	//BoostScan();

	std::string targetPath = "E:\\转辙机数据\\";
	boost::filesystem::path savePath(targetPath);

	boost::filesystem::directory_iterator endIter;
	for (boost::filesystem::directory_iterator iter(savePath); iter != endIter; iter++) {
		if (!boost::filesystem::is_directory(*iter))
			continue;

        std::string strDate = iter->path().filename().string();

		if (!CheckDateValid(strDate))
			continue;
        
        SYSTEMTIME sysTime1;
        sscanf_s(strDate.c_str(), "%4d%2d%2d", &sysTime1.wYear, &sysTime1.wMonth, &sysTime1.wDay);

        struct tm gm = { 0,0,0,sysTime1.wDay,sysTime1.wMonth - 1,sysTime1.wYear - 1900,0,0,0 };
        time_t time = mktime(&gm);

        tm temptm;
        localtime_s(&temptm,&time);
        SYSTEMTIME st = { 1900 + temptm.tm_year,
            1 + temptm.tm_mon,
            temptm.tm_wday,
            temptm.tm_mday,
            temptm.tm_hour,
            temptm.tm_min,
            temptm.tm_sec,
            0 };

        char chData[32];

        sprintf_s(chData,"%4d%02d%02d%02d%02d%02d %lld", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, time);

        std::cout << chData << std::endl;

        std::cout << iter->path().string() << std::endl;

        std::string  imgpath = iter->path().string() + "\\70-B5-E8-32-2F-3B天回镇采样机1号\\过车记录";
        boost::filesystem::path subPath(imgpath);

        boost::filesystem::directory_iterator timeEndIter;
        for (boost::filesystem::directory_iterator timeiter(subPath); timeiter != timeEndIter; timeiter++) {

            std::string strTime = timeiter->path().filename().string();

            if (!CheckTimeValid(strTime))
                continue;

            SYSTEMTIME sysTime2;
            std::string strDatatime = strDate + strTime;
            sscanf_s(strDatatime.c_str(), "%4d%2d%2d%2d%2d%2d", &sysTime2.wYear, &sysTime2.wMonth, &sysTime2.wDay, &sysTime2.wHour, &sysTime2.wMinute, &sysTime2.wSecond);

            std::string imgFullPath = timeiter->path().string() + "\\监测1\\图像.jpg";
            std::string imginfoFullPath = timeiter->path().string() + "\\监测1\\图像说明.txt";

            if (IsFileExistent(imgFullPath))
            {
                long long  imgsize = boost::filesystem::file_size(imgFullPath);
                std::cout << imgFullPath << " size:" << imgsize << std::endl;
            }

            if (IsFileExistent(imginfoFullPath))
            {
                std::cout << imginfoFullPath << std::endl;
                std::ifstream ifs(imginfoFullPath);
                // get the size of file
                ifs.seekg(0, std::ios::end);
                std::streampos length = ifs.tellg();
                ifs.seekg(0, std::ios::beg);

                std::shared_ptr<char> shbuffer = std::shared_ptr<char>(new char[length], [](char* p) {delete[] p; });
                ifs.read(shbuffer.get(), length);
                ifs.close();
                std::string contents(shbuffer.get());
                std::cout << contents << std::endl;
            }
        }
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
