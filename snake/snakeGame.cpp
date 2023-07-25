#include "snakeGame.h"
#include <stdio.h>
#include <iostream>

float SnakeGame::getDistance(float x1, float y1, float x2, float y2)
{
	return powf(x2 - x1, 2) + powf(y2 - y1, 2);
}

SnakeGame::SnakeGame(int screenWidth, int screenHeight, int w, int h)
{
	width = w;
	height = h;
	cellWidth = screenWidth / width;
	cellHeight = screenHeight / height;
	snakePlayer = new Snake(w / 2, h / 2);
	for (int i = 0; i < 0; i++)
	{
		snakePlayer->addBody(width, height);
	}
	apple = new Apple(rand() % (width - 1), rand() & (height - 1));
	score = 0;
	length = 0;

	audio = new AudioManager();
	audio->loadSound("audio\\snake_turn.wav", 0);
	audio->loadSound("audio\\pick_apple.wav", 1);
	audio->loadSound("audio\\milestone.wav", 2);

	running = true;
}

SnakeGame::~SnakeGame()
{
	delete snakePlayer;
}

void SnakeGame::render(SDL_Renderer* renderer)
{
#if 0 // Render Grid
	// Render grid
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			SDL_Rect renderRect = { i * cellWidth, j * cellHeight, cellWidth, cellHeight };
			SDL_RenderDrawRect(renderer, &renderRect);
		}
	}
#endif

	// Render snake
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);

	Coordinates snakeHead = snakePlayer->getHead();
	std::vector<Coordinates> snakeBody = snakePlayer->getBody();

	SDL_Rect headRenderRect{ snakeHead.x * cellWidth, snakeHead.y * cellHeight, cellWidth, cellHeight };
	SDL_RenderFillRect(renderer, &headRenderRect);
	for (int i = 0; i < snakeBody.size() - 1; i++)
	{
		SDL_Rect renderRect{ snakeBody.at(i).x * cellWidth, snakeBody.at(i).y * cellHeight, cellWidth, cellHeight };
		SDL_RenderFillRect(renderer, &renderRect);
	}

	// Render apple
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	SDL_Rect appleRenderRect{ apple->getLocation().x * cellWidth, apple->getLocation().y * cellHeight, cellWidth, cellHeight };
	SDL_RenderFillRect(renderer, &appleRenderRect);
}

void SnakeGame::nextFrame(int& flags)
{
	audio->update();

	flags = 0;

	snakePlayer->move();

	if (snakePlayer->getHead().x > width || snakePlayer->getHead().x < 0)
		flags = 1;
	if (snakePlayer->getHead().y > height || snakePlayer->getHead().y < 0)
		flags = 1;
	if (snakePlayer->checkSnakeCollision())
		flags = 1;

	if (snakePlayer->getHead() == apple->getLocation()) {
		audio->playSound(1);
		snakePlayer->addBody(width, height);
		do {
			apple->newLocation(width, height);
		} while (snakePlayer->checkBodyCoordinates(apple->getLocation()));
		score ++;
		length++;

		if (score % 10 == 0) {
			audio->playSound(2);
		}
	}

	if (snakePlayer->getBody().size() == (width * height) - 1)
		flags = 2;

	if (flags == 1 || flags == 2)
	{
		running = false;
	}
}

void SnakeGame::setSnakeDirection(int d)
{
	bool playSound = true;
	switch (d)
	{
	case RIGHT:
		if (snakePlayer->getDirection() == LEFT) {
			playSound = false;
			d = LEFT;
		}
		break;
	case UP:
		if (snakePlayer->getDirection() == DOWN) {
			playSound = false;
			d = DOWN;
		}
		break;
	case LEFT:
		if (snakePlayer->getDirection() == RIGHT) {
			playSound = false;
			d = RIGHT;
		}
		break;
	case DOWN:
		if (snakePlayer->getDirection() == UP) {
			playSound = false;
			d = UP;
		}
		break;
	}

	if (snakePlayer->getDirection() == d)
		playSound = false;

	if (playSound)
		audio->playSound(0);
	snakePlayer->setDirection(d);
}

void SnakeGame::reset()
{
	snakePlayer->setHeadLocation(width / 2, height / 2);
	snakePlayer->clearBody();
	apple->setLocation(rand() % (width - 1), rand() & (height - 1));
	score = 0;
	length = 0;

	running = true;
}

int SnakeGame::getWidth()
{
	return width;
}

int SnakeGame::getHeight()
{
	return height;
}

int SnakeGame::getScore()
{
	return score;
}

bool SnakeGame::isRunning()
{
	return running;
}