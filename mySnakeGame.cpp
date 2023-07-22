#include <stdio.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <string>
#include "snake/snakeGame.h"

#define FPS 60

enum gameStates
{
	MAIN_MENU,
	IN_GAME,
	QUITTING_GAME,
	TOTAL_GAME_STATES
};

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

const int GAME_WIDTH = 40;
const int GAME_HEIGHT = 40;

int gameFlags;
int currentState = MAIN_MENU;

Uint32 fps_nextTime = 1000 / 5;

enum buttonStates { MOUSE_DOWN, MOUSE_UP };

// Initializes SDL
bool init();

// Closes and deallocates all data related to SDL
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SnakeGame* snakeGame;
int gameScore;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize. SDL ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering is not enabled." << std::endl;
	}

	gWindow = SDL_CreateWindow("Snake Reinforcment Learning", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Failed to create Window. SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		std::cout << "Failed to create renderer. SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "Failed to initialize TTF.TTF_ERROR: " << TTF_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);

	snakeGame = new SnakeGame(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_WIDTH, GAME_HEIGHT);
	return true;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	SDL_Quit();
}

void renderText(int x, int y, const char* string, int fontSize, const char* font)
{
	TTF_Font* ttfFont = TTF_OpenFont(font, fontSize);
	if (ttfFont == nullptr)
	{
		std::cout << "Error opening font. TTF_ERROR: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Color colour = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Surface* surf = TTF_RenderText_Blended(ttfFont, string, colour);
	if (surf == nullptr)
	{
		TTF_CloseFont(ttfFont);
		std::cout << "Error converting font to surface. TTF_ERROR: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surf);
	if (texture == nullptr)
	{
		SDL_FreeSurface(surf);
		std::cout << "Error converting surface to texture. SDL_ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_Rect textRect{ x, y, surf->w, surf->h };
	SDL_RenderCopy(gRenderer, texture, NULL, &textRect);

	TTF_CloseFont(ttfFont);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

void renderUI()
{
	renderText(0, 0, std::to_string(snakeGame->getScore()).c_str(), 24, "Arial.ttf");
}

void render()
{
	// std::cout << "Rendering iteration " << bestIteration << std::endl;
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);
	SDL_RenderClear(gRenderer);
	snakeGame->render(gRenderer);
	renderUI();
	SDL_RenderPresent(gRenderer);
}

void update()
{
	snakeGame->nextFrame(gameFlags);

	if (gameFlags == 1 || gameFlags == 2)
	{
		currentState = QUITTING_GAME;
	}
}

void capFrameRate()
{
	while (SDL_GetTicks() < fps_nextTime) {}
	fps_nextTime += 1000 / FPS;
}

int main(int argc, char* args[])
{
	if (!init())
	{
		std::cout << "Failed to initialize SDL." << std::endl;
	}
	else
	{
		std::cout << "Running program." << std::endl;

		bool quit = true;
		SDL_Event e;

		while (quit)
		{
			SDL_Delay(50);
			while (SDL_PollEvent(&e) > 0)
			{
				switch (e.type) {
				case SDL_QUIT:
					currentState = QUITTING_GAME;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_d:
						snakeGame->setSnakeDirection(RIGHT);
						break;
					case SDLK_w:
						snakeGame->setSnakeDirection(UP);
						break;
					case SDLK_a:
						snakeGame->setSnakeDirection(LEFT);
						break;
					case SDLK_s:
						snakeGame->setSnakeDirection(DOWN);
						break;
					}
					break;
				}
			}

			update();

			render();

			capFrameRate();

			if (currentState == QUITTING_GAME)
			{
				quit = false;
			}
		}
	}

	close();

	return 0;
}