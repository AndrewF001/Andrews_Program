#pragma once
#include <chrono>

class StopWatch
{
	public:
		StopWatch();
		void Start();
		void Pause();
		void Restart();
		long long Duration();

	private:
		std::chrono::high_resolution_clock::time_point T1;
		std::chrono::high_resolution_clock::duration Dur;

};

