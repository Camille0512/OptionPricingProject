/**
* Author: Zhixin Li
* File name: StopWatch.hpp
* Date: 2023.03.10
* Description: The header file for the StopWatch
* Version: 1.0
* */

#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class StopWatch
{
private:
	StopWatch(const StopWatch&);
	StopWatch& operator=(const StopWatch&);

	// Add data member
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;

public:
	StopWatch();
	virtual ~StopWatch();
	
	void StartStopWatch();
	void StopStopWatch();
	void Reset();

	double GetTime() const;
};

#endif