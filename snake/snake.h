#pragma once
#include <vector>
#include <dataStructures.h>

enum SNAKE_DIRECTIONS { RIGHT, UP, LEFT, DOWN };

class Snake {
	Coordinates head;
	std::vector<Coordinates> body; // Snake will start with one, which is not actually part of the snake's body but act as a placeholder for the next one.
	int direction; // 0 = Right, 1 = Up, 2 = Left, 3 = Down

public:
	Snake(int x = 0, int y = 0);
	~Snake();
	void addBody(int width, int height);
	void move();
	// Checks if the head collides with any part of the body. Returns true if there is collision, otherwise return false.
	bool checkSnakeCollision();
	// Checks if the given coordinates match the head or any of the body (except for the last one). True if there is a collision, false otherwise.
	bool checkBodyCoordinates(Coordinates c);
	void clearBody();

	Coordinates getHead();
	std::vector<Coordinates> getBody();
	int getDirection();

	void setDirection(int d);
	void setHeadLocation(int x, int y);
};