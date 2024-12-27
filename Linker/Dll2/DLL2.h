#pragma once
#ifndef __dllexport__
#define __DLL__ __declspec(dllimport)
#else
#define __DLL__ __declspec(dllexport)
#endif

#include "../DLL/DLL.h"

extern "C" __DLL__ DLL* GetInst();
extern "C" __DLL__ void FreeInst();

class __DLL__ DLL2: public DLL
{
public:
	DLL2();
	~DLL2();

public:
	void Process();
};

