// TestNJson.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include ".\nlohmann\json.hpp"

using nlohmann::json;

int main()
{
    //std::string strMsg = "{\"index\":1,\"type\" : 1,\"operation\" : {\"subindex\":2,\"subtype\":3}}";

    //json j = json::parse(strMsg);

    //try
    //{
    //    int a = j["a"];
    //}
    //catch (...)
    //{
    //    std::cout << "解析json出错 "<< std::endl;
    //}

    //std::string jopration = j["operation"];

    //std::cout << "index " << j["index"] << std::endl;
    //std::cout << "type " << j["type"] << std::endl;
    //std::cout << "operation " << jopration << std::endl;

    //j["deviceCode"] = 2;

    //std::cout << j.dump() << std::endl;

    json j1, jsub1;

    jsub1["fileTime"] = 133240966796410292;
    jsub1["optype"] = std::string("车牌识别");
    jsub1["camId"] = 10001;
    jsub1["weighDevId"] = 10002;

    j1["index"] = 1;
    j1["type"] = 1;
    j1["operation"] = jsub1;

    std::cout << j1.dump() << std::endl;
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
