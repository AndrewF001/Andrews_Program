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
	//Duration += std::chrono::high_resolution_clock::now() - T1;
	Dur += T1.time_since_epoch();
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