#pragma once
#include <dataStructures.h>

class Apple {
	Coordinates location;

public:
	Apple(int x = 0, int y = 0);
	~Apple();
	void newLocation(int gridWidth, int gridHeight);

	Coordinates getLocation();

	void setLocation(int x, int y);
};
