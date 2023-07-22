#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "snake.h"
#include "apple.h"
#include <math.h>

class SnakeGame {
	int width;
	int height;
	int cellWidth;
	int cellHeight;
	int score;
	int length;
	Snake* snakePlayer;
	Apple* apple;

	bool running;

	float getDistance(float x1, float y1, float x2, float y2);

public:
	SnakeGame(int screenWidth, int screenHeight, int w = 10, int h = 10);
	~SnakeGame();
	void render(SDL_Renderer* renderer);
	// Performs the game logic for the next frame
	// Also takes in a parameter for gameFlags
	// 0 = game is running, 1 = game lost, 2 = game win
	void nextFrame(int& flags);
	void reset();

	void setSnakeDirection(int d);

	int getWidth();
	int getHeight();
	int getScore();
	bool isRunning();
};