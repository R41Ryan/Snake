#include "snake.h"

Snake::Snake(int x, int y)
{
	Coordinates firstBody;
	firstBody.x = x - 1;
	firstBody.y = y;
	if (x == 0) {
		firstBody.x = 1;
	}
	head.x = x;
	head.y = y;

	body.push_back(firstBody);

	direction = RIGHT;
}

Snake::~Snake()
{
	body.clear();
}

void Snake::addBody(int width, int height)
{
	std::vector<Coordinates> availableBodySpots;

	if (body.back().x > 0)
	{
		Coordinates* newBody = new Coordinates(body.back().x - 1, body.back().y);
		if (!checkBodyCoordinates(*newBody))
			availableBodySpots.push_back(*newBody);
	}
	if (body.back().x < width - 1)
	{
		Coordinates* newBody = new Coordinates(body.back().x + 1, body.back().y);
		if (!checkBodyCoordinates(*newBody))
			availableBodySpots.push_back(*newBody);
	}
	if (body.back().y > 0)
	{
		Coordinates* newBody = new Coordinates(body.back().x, body.back().y - 1);
		if (!checkBodyCoordinates(*newBody))
			availableBodySpots.push_back(*newBody);
	}
	if (body.back().y < height - 1)
	{
		Coordinates* newBody = new Coordinates(body.back().x, body.back().y + 1);
		if (!checkBodyCoordinates(*newBody))
			availableBodySpots.push_back(*newBody);
	}

	Coordinates newBody = availableBodySpots.at(rand() % availableBodySpots.size());
	body.push_back(newBody);
}

void Snake::move()
{
	for (int i = body.size() - 1; i > 0; i--)
	{
		body.at(i).x = body.at(i - 1).x;
		body.at(i).y = body.at(i - 1).y;
	}

	body.at(0).x = head.x;
	body.at(0).y = head.y;

	switch (direction)
	{
	case RIGHT:
		head.x += 1;
		break;
	case UP:
		head.y -= 1;
		break;
	case LEFT:
		head.x -= 1;
		break;
	case DOWN:
		head.y += 1;
		break;
	}
}

bool Snake::checkSnakeCollision()
{
	for (int i = 0; i < body.size() - 1; i++)
	{
		if (head == body.at(i))
			return true;
	}
	return false;
}

bool Snake::checkBodyCoordinates(Coordinates c)
{
	if (c == head) return true;
	for (int i = 0; i < body.size() - 1; i++) {
		if (c == body.at(i)) return true;
	}
	return false;
}

void Snake::clearBody()
{
	body.clear();
	Coordinates firstBody;
	firstBody.x = head.x - 1;
	firstBody.y = head.y;
	if (head.x == 0) {
		firstBody.x = 1;
	}

	body.push_back(firstBody);
}

Coordinates Snake::getHead()
{
	return head;
}

std::vector<Coordinates> Snake::getBody()
{
	return body;
}

int Snake::getDirection()
{
	return direction;
}

void Snake::setDirection(int d)
{
	direction = d;
}

void Snake::setHeadLocation(int x, int y)
{
	head.x = x;
	head.y = y;
}