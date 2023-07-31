#include "timer.h"

Timer::Timer(int wt)
{
	waitTime = wt;
	endTime = SDL_GetTicks64();
	running = false;
}

void Timer::start()
{
	endTime = SDL_GetTicks64() + waitTime;
	running = true;
}

void Timer::stop()
{
	endTime = SDL_GetTicks64();
	running = false;
}

bool Timer::update()
{
	if (running) {
		if (SDL_GetTicks64() >= endTime)
		{
			running = false;
			return true;
		}
	}
	return false;
}
