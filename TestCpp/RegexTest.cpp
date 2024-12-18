#include "RegexTest.h"
#include <regex>
#include <list>
#include <iostream>
#include <map>

void RegexTest()
{
	std::regex reg("Cam[0-9]-[0-9]+");
	
	std::list<std::string> list;
	list.push_back("M123-32");
	list.push_back("123-32");
	list.push_back("M123-3M2");
	list.push_back("M123-3");
	list.push_back("M123-");
	list.push_back("M123");

	for(std::string  str : list)
	{
		if (std::regex_match(str, reg))
			std::cout << str << " 符合 " << str.substr(0,str.find_first_of("_")) << std::endl;
		else
			std::cout << str << " 不符合" << std::endl;
	}

	std::map<std::string, std::string> mapStr;
	std::map<std::string, std::string >::iterator it;
	it = mapStr.find("ABC");
	if(it != mapStr.end())
		std::cout << (*it).first << "  " << (*it).second << std::endl;

	mapStr.insert(std::pair<std::string, std::string >("AAC", "123"));
	
	it = mapStr.find("AAC");
	if (it != mapStr.end())
		std::cout << (*it).first << "  " << (*it).second << std::endl;


	std::regex reg2("Cam[3,6]_[0-9]{3}.jpg");

	std::list<std::string> list2;
	list2.push_back("___3_001.jpg");
	list2.push_back("Cam6_001.jpg");
	list2.push_back("Cam6_135.jpg");
	list2.push_back("Cam6_13.jpg");
	list2.push_back("Cam4_135.jpg");
	list2.push_back("Cam3_135.jpg");
	list2.push_back("Cam2_135.jpg");
	list2.push_back("Cam5_135.jpg");
	list2.push_back("Cam7_135.jpg");

	for (std::string str : list2)
	{
		if (std::regex_match(str, reg2))
			std::cout << str << " 符合 "  << std::endl;
		else
			std::cout << str << " 不符合" << std::endl;
	}
}