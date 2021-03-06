#pragma once
#include <chrono>
/*
	Basic timer using Chrono
*/
class StopWatch
{
	public:
		StopWatch();
		void Start();
		void Pause();
		void Restart();
		long long Duration();

	private:
		std::chrono::steady_clock::time_point T1;
		std::chrono::steady_clock::duration Dur;

};

