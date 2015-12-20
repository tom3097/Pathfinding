#pragma once

#include <chrono>

class Timer
{
private:
	/* Timer creation time */
	std::chrono::high_resolution_clock::time_point start;
public:
	Timer();
	~Timer();

	/* Measure estimated time 
	 * @returns {long long}: measured time value
	 */
	long long getEstimatedTime();
};

