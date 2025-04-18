#pragma once
#include <windows.h>

class QPC
{
public:
	QPC() : a({ 0 }), start({ 0 }), freq({ 0 }), end({ 0 })
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
	}

	void GetHighresolutiontime();
	LARGE_INTEGER a;

private:
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
};
