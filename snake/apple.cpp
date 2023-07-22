#include "apple.h"
#include <cstdlib>

Apple::Apple(int x, int y)
{
	location.x = x;
	location.y = y;
}

Apple::~Apple()
{
}

void Apple::newLocation(int gridWidth, int gridHeight)
{
	location.x = rand() % gridWidth;
	location.y = rand() % gridHeight;
}

Coordinates Apple::getLocation()
{
	return location;
}

void Apple::setLocation(int x, int y)
{
	location.x = x;
	location.y = y;
}