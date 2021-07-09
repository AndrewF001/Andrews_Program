#include "StopWatch.h"

StopWatch::StopWatch()
{
	T1 = std::chrono::high_resolution_clock::now();
	Dur.zero();
}

void StopWatch::Start()
{
	T1 = std::chrono::high_resolution_clock::now();
}

void StopWatch::Pause()
{
	//Duration += std::chrono::high_resolution_clock::now() - T1;
	Dur += T1.time_since_epoch();
}

void StopWatch::Restart()
{
	T1 = std::chrono::high_resolution_clock::now();
	Dur.zero();
}

long long StopWatch::Duration()
{
	return Dur.count();
}