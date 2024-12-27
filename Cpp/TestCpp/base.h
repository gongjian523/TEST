#pragma once

#include <Memory>

class Base
{
public:
	Base();
	~Base();

private:
	std::shared_ptr<int> buf;

};
