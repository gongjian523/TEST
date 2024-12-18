#pragma once

#ifndef __dllexport__
#define __DLL__ __declspec(dllimport)
#else
#define __DLL__ __declspec(dllexport)
#endif

__DLL__ void StartDll1();
__DLL__ void StopDll1();

class DLL1
{
public:
	DLL1();
	~DLL1();
	void Start();

	void Stop();


};

