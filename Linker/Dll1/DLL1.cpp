#include "DLL1.h"
#include <iostream>

DLL* pDLL = nullptr;

DLL* GetInst() {
	pDLL = new DLL1();
	return pDLL;
}

void FreeInst() {
	if (pDLL != nullptr)
		delete (DLL1*)pDLL;
}

DLL1::DLL1() {
	std::cout << "DLL1 ctor " << std::endl;
}

DLL1::~DLL1() {
	std::cout << "DLL1 dtor " << std::endl;
}

void DLL1::Process() {
	std::cout << "DLL1 Process " << std::endl;
}