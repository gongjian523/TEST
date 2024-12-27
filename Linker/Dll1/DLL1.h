#pragma once

#ifndef __dllexport__
#define __DLL__ __declspec(dllimport)
#else
#define __DLL__ __declspec(dllexport)
#endif

//__DLL__ void StartDll1();
//__DLL__ void StopDll1();

#include "../DLL/DLL.h"

extern "C" __DLL__ DLL* GetInst();
extern "C" __DLL__ void FreeInst();

 class __DLL__ DLL1: public DLL
{
public:
	DLL1();
	~DLL1();

public:
	//void Start();
	//void Stop();
	
	void Process();
};

