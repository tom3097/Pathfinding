#include "Timer.h"



Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
}


long long Timer::getEstimatedTime()
{
	auto measuredTime = std::chrono::high_resolution_clock::now() - start;
	long long measuredTimeNano = std::chrono::duration_cast<std::chrono::milliseconds>(measuredTime).count();
	return measuredTimeNano;
}
