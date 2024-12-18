#pragma once
#ifndef __dllexport__
#define __DLL__ __declspec(dllimport)
#else
#define __DLL__ __declspec(dllexport)
#endif


class __DLL__ DLL2
{
public:

	DLL2();
	~DLL2();
	void Process();
};

