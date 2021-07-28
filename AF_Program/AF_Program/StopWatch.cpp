#include "StopWatch.h"

StopWatch::StopWatch()
{
	T1 = std::chrono::steady_clock::now();
	Dur = std::chrono::steady_clock::duration::zero();
}

void StopWatch::Start()
{
	T1 = std::chrono::steady_clock::now();
}

void StopWatch::Pause()
{
	Dur += std::chrono::steady_clock::now() - T1;
}

void StopWatch::Restart()
{
	T1 = std::chrono::steady_clock::now();
	Dur = std::chrono::steady_clock::duration::zero();
}

long long StopWatch::Duration()
{
	return Dur.count();
}