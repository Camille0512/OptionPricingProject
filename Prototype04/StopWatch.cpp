/**
* Author: Zhixin Li
* File name: StopWatch.hpp
* Date: 2023.03.10
* Description: The implementation file for the StopWatch
* Version: 1.0
* */

#include "StopWatch.hpp"

using std::chrono::system_clock;
using std::chrono::duration;
using std::milli;

// Default Constructor
StopWatch::StopWatch() {}

// Copy Constructor - private
StopWatch::StopWatch(const StopWatch& obj) : start(obj.start), end(obj.end) {}

// Destructor
StopWatch::~StopWatch() {}

// Operator - private
StopWatch& StopWatch::operator=(const StopWatch& obj)
{
	if (this == &obj)
	{ // Avoid self-assignment
		return *this;
	}
	else
	{
		start = obj.start; end = obj.end; return *this;
	}
}

void StopWatch::StartStopWatch()
{
	start = system_clock::now();
}

void StopWatch::StopStopWatch()
{
	end = system_clock::now();
}

void StopWatch::Reset()
{
	start = std::chrono::time_point<std::chrono::system_clock>{};
	end = std::chrono::time_point<std::chrono::system_clock>{};
}

double StopWatch::GetTime() const
{
	duration<double, milli> res = end - start;
	return res.count();
}