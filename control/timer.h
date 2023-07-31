#pragma once
#include <SDL.h>

class Timer {
	Uint64 waitTime;
	Uint64 endTime;
	bool running;

public:
	Timer(int wt = 10000);
	
	void start();
	void stop();

	// Returns true if time just ended, false otherwise.
	bool update();

	Uint64 getWaitTime() { return waitTime; }
	Uint64 getEndTime() { return endTime; };
	Uint64 getTimeLeft() { return SDL_GetTicks64() - endTime; }
	bool isRunning() { return running; }

	void setWaitTime(Uint64 t) { waitTime = t; }
	void setEndTime(Uint64 t) { endTime = t; }
};