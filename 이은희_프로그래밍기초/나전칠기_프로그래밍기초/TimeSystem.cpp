#include "TimeSystem.h"

void QPC::GetHighresolutiontime()
{
	QueryPerformanceCounter(&end);
	a.QuadPart = (end.QuadPart - start.QuadPart) / freq.QuadPart;
}