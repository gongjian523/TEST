
#include "base.h"

#include<iostream>

Base::Base()
{
	std::cout << "Base" << std::endl;
	buf = std::shared_ptr<int>(new int[10], [](int* p) {delete[] p;
		std::cout << "ÊÍ·ÅÄÚ´æ" << std::endl;
	});
}

Base::~Base()
{
	std::cout << "~Base" << std::endl;
}