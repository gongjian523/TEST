#include "DLL2.h"
#include <iostream>


DLL2::DLL2() {
	std::cout << "DLL2 ctor " << std::endl;
}

DLL2::~DLL2() {
	std::cout << "DLL2 dtor " << std::endl;
}

void DLL2::Process() {
	std::cout << "DLL2 Process " << std::endl;
}
