#include "DLL1.h"
#include <iostream>


DLL1::DLL1() {
	std::cout << "DLL1 ctor " << std::endl;
}

DLL1::~DLL1() {
	std::cout << "DLL1 dtor " << std::endl;
}

void DLL1::Process() {
	std::cout << "DLL1 Process " << std::endl;
}