#include "StringTest.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

void StringNullTest()
{
	std::string str1 = "", str2 = "";
	std::cout << "1 " << std::endl;
	if ((str1 != "" && str2 != ""))
		std::cout << "none is null" << std::endl;

	str1 = "111";
	std::cout << "2 " << std::endl;
	if ((str1 != "" && str2 != ""))
		std::cout << "none is null" << std::endl;

	str2 = "111";
	std::cout << "3 " << std::endl;
	if ((str1 != "" && str2 != ""))
		std::cout << "none is null" << std::endl;

	str2 = "111";
	std::cout << "4 " << std::endl;
	if ((str1 != "" && str2 != ""))
		std::cout << "none is null" << std::endl;

}

/*********************************************************************************************/

std::vector<std::string> vStringSplit(const  std::string& s, const std::string& delim = ",")
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

void StringSplitTest() 
{
    auto res = vStringSplit("a,b,c");
    for (int i = 0;i < res.size();i++) {
        std::cout << res[i] << std::endl;
    }
    auto res1 = vStringSplit("1,2,3");
    for (int i = 0;i < res1.size();i++) {
        std::cout << res1[i] << std::endl;
    }

    auto res2 = vStringSplit("12");
    for (int i = 0;i < res2.size();i++) {
        std::cout << res2[i] << std::endl;
    }
}

/*********************************************************************************************/

void StringAssginTest()
{
    char* pString = new char[256] { 0 };
    std::string str1 = "This is the string1.";
    memcpy_s(pString, str1.length(), str1.c_str(), str1.length());
    std::string str2;
    str2.assign(pString, 256);
    delete[] pString;
    str1 = "This is a new string - string2.";
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
}

/*********************************************************************************************/

void StirngSystemConvertTest()
{
    SYSTEMTIME curTime;
    ::GetLocalTime(&curTime);

    char aDateTimeStrScr[MAX_PATH] = { 0 };
    sprintf_s(aDateTimeStrScr, "%04d-%02d-%02d %02d:%02d:%02d.%03d", curTime.wYear,curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond, curTime.wMilliseconds);
    std::string strDate = aDateTimeStrScr;

    char aDateTimeStrDes[MAX_PATH] = { 0 };
    memcpy_s(aDateTimeStrDes, strDate.length(), strDate.c_str(), strDate.length());

    SYSTEMTIME lastTime = {};
    sscanf_s(aDateTimeStrScr, "%04d-%02d-%02d %02d:%02d:%02d.%03d", &lastTime.wYear, &lastTime.wMonth, &lastTime.wDay, &lastTime.wHour, &lastTime.wMinute, &lastTime.wSecond, &lastTime.wMilliseconds);

    std::cout << "Scr " << curTime.wYear << "-" << curTime.wMonth << "-" << curTime.wDay << " " << curTime.wHour << ":" << curTime.wMinute << ":" << curTime.wSecond << "." << curTime.wMilliseconds << std::endl;
    std::cout << "Des " << lastTime.wYear << "-" << lastTime.wMonth << "-" << lastTime.wDay << " " << lastTime.wHour << ":" << lastTime.wMinute << ":" << lastTime.wSecond << "." << lastTime.wMilliseconds << std::endl;
}


/*********************************************************************************************/

std::string GetCurHourSystemTimeV5()
{
    FILETIME fTimeLocal = {};
    FILETIME fTime = {};
    SYSTEMTIME sysTime = {};

    GetSystemTimeAsFileTime(&fTime);
    FileTimeToLocalFileTime(&fTime, &fTimeLocal);

    FileTimeToSystemTime((&fTimeLocal), &sysTime);

    char str[256] = { 0 };
    sprintf_s(str, "%04d%02d%02d%02d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    std::string retString = str;
    return retString;
}

void StirngRelpaceTest()
{
    
    std::string desFilePath = "E:\\视频数据\\20220411\\成都地铁10号线175317_(上行)\\20220411183157_金花-1航楼.mkv";
    std::string fileName = desFilePath;
    
    size_t pos = fileName.find_last_of("\\");

    if (pos != std::string::npos)
        desFilePath = fileName.substr(0, pos);

    std::string szOldFile = fileName.substr(pos + 1);

    size_t pos1 = szOldFile.find_last_of("_");
    if (pos != std::string::npos)
    {
        desFilePath = desFilePath + "\\" + GetCurHourSystemTimeV5() + szOldFile.substr(pos1);
    }

    size_t pos2 = fileName.find_last_of("金花-1航楼");

    size_t pos3 = fileName.find_last_of("assdfa");
    std::cout << desFilePath << std::endl;
}


/*********************************************************************************************/

void StringTest()
{
    //StringNullTest();
    //StringSplitTest();
    //StringAssginTest();
    //StirngSystemConvertTest();
    StirngRelpaceTest();
}