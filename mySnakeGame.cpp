#include <stdio.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "snake/snakeGame.h"
#include "ui/ui.h"
#include "control/control.h"

#define FPS 30
#define GLOBAL_SOUNDS_NUM 10

enum gameStates
{
	MAIN_MENU,
	IN_GAME,
	GAME_OVER,
	QUITTING_GAME,
	TOTAL_GAME_STATES
};

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

const int GAME_WIDTH = 40;
const int GAME_HEIGHT = 40;

int gameFlags;
int currentState = MAIN_MENU;
bool paused = false;

Uint32 fps_nextTime = 1000 / 5;

// Initializes SDL
bool init();

// Closes and deallocates all data related to SDL
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Coordinates mousePos;

AudioManager* globalAudio;

SnakeGame* snakeGame;
int gameScore;

Menu* mainMenu;
Menu* pauseMenu;
Menu* gameOverMenu;

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to initialize mixer." << std::endl;
		return false;
	}

	globalAudio = new AudioManager();
	globalAudio->loadSound("audio\\forward.wav", 0);
	globalAudio->loadSound("audio\\backward.wav", 1);
	globalAudio->loadSound("audio\\pause.wav", 2);
	globalAudio->loadSound("audio\\unpause.wav", 3);

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);

	snakeGame = new SnakeGame(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

	mainMenu = new Menu(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4);
	ButtonUI* mainMenuButton = new ButtonUI(Coordinates(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), "Start Game", Vector2D<int>(200, 100), "Arial.ttf", 15);
	mainMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	mainMenu->addButton(mainMenuButton);
	mainMenuButton = new ButtonUI(Coordinates(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Sound On", Vector2D<int>(200, 100), "Arial.ttf", 15);
	mainMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	mainMenu->addButton(mainMenuButton);
	mainMenuButton = new ButtonUI(Coordinates(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Exit Game", Vector2D<int>(200, 100), "Arial.ttf", 15);
	mainMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	mainMenu->addButton(mainMenuButton);

	pauseMenu = new Menu(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	ButtonUI* pauseMenuButton = new ButtonUI(Coordinates(), "Resume", Vector2D<int>(200, 100), "Arial.ttf", 15);
	pauseMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	pauseMenu->addButton(pauseMenuButton);
	pauseMenuButton = new ButtonUI(Coordinates(), "Sound On", Vector2D<int>(200, 100), "Arial.ttf", 15);
	pauseMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	pauseMenu->addButton(pauseMenuButton);
	pauseMenuButton = new ButtonUI(Coordinates(), "Return to Menu", Vector2D<int>(200, 100), "Arial.ttf", 15);
	pauseMenuButton->getAudio()->loadSound("audio\\hover.wav", 0);
	pauseMenu->addButton(pauseMenuButton);

	gameOverMenu = new Menu(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 3 / 4);
	ButtonUI* gameOverButton = new ButtonUI(Coordinates(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Play Again", Vector2D<int>(200, 100), "Arial.ttf", 15);
	gameOverButton->getAudio()->loadSound("audio\\hover.wav", 0);
	gameOverMenu->addButton(gameOverButton);
	gameOverButton = new ButtonUI(Coordinates(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "Exit Game", Vector2D<int>(200, 100), "Arial.ttf", 15);
	gameOverButton->getAudio()->loadSound("audio\\hover.wav", 0);
	gameOverMenu->addButton(gameOverButton);

	return true;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	delete globalAudio;

	Mix_CloseAudio();
	TTF_Quit();
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

	switch (currentState)
	{
	case MAIN_MENU:
		mainMenu->render(gRenderer);
		break;
	case IN_GAME:
		snakeGame->render(gRenderer);
		renderUI();
		if (paused) {
			pauseMenu->render(gRenderer);
		}
		break;
	case GAME_OVER:
		gameOverMenu->render(gRenderer);
		break;
	default:
		break;
	}
	SDL_RenderPresent(gRenderer);
}

void update()
{
	globalAudio->update();
	switch (currentState) 
	{
	case MAIN_MENU:
		mainMenu->update(mousePos);
		break;
	case IN_GAME:
		if (!paused) {
			snakeGame->nextFrame(gameFlags);

			switch (gameFlags)
			{
			case 1:
				globalAudio->playSound(1);
				currentState = GAME_OVER;
				break;
			case 2:
				currentState = GAME_OVER;
				break;
			}
		}
		else {
			pauseMenu->update(mousePos);
		}
		break;
	case GAME_OVER:
		gameOverMenu->update(mousePos);
		break;
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
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			while (SDL_PollEvent(&e) > 0)
			{
				switch (e.type)
				{
				case SDL_QUIT:
					currentState = QUITTING_GAME;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
					case SDLK_d:
						if (currentState == IN_GAME && !paused) {
							snakeGame->setSnakeDirection(RIGHT);
						}
						break;
					case SDLK_w:
						if (currentState == IN_GAME && !paused) {
							snakeGame->setSnakeDirection(UP);
						}
						break;
					case SDLK_a:
						if (currentState == IN_GAME && !paused) {
							snakeGame->setSnakeDirection(LEFT);
						}
						break;
					case SDLK_s:
						if (currentState == IN_GAME && !paused) {
							snakeGame->setSnakeDirection(DOWN);
						}
						break;
					case SDLK_ESCAPE:
						if (currentState == IN_GAME) {
							paused = paused == false;
							if (paused) {
								globalAudio->playSound(2);
							}
							else {
								globalAudio->playSound(3);
							}
						}
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (e.button.button)
					{
					case SDL_BUTTON_LEFT:
						switch (currentState) {
						case MAIN_MENU:
						{
							int clickedButton = mainMenu->isIn(mousePos);
							switch (clickedButton) {
							case 0:
								snakeGame->reset();
								currentState = IN_GAME;
								globalAudio->playSound(0);
								break;
							case 1:
								AudioManager::setEnableSound(AudioManager::getEnableSound() == false);
								globalAudio->playSound(0);
								if (AudioManager::getEnableSound()) {
									mainMenu->getButtons()[1]->setText("Sound On");
									pauseMenu->getButtons()[1]->setText("Sound On");
								}
								else {
									mainMenu->getButtons()[1]->setText("Sound Off");
									pauseMenu->getButtons()[1]->setText("Sound Off");
								}
								break;
							case 2:
								currentState = QUITTING_GAME;
								break;
							}
							break;
						}
						case IN_GAME:
						{
							int clickedButton = pauseMenu->isIn(mousePos);
							switch (clickedButton) {
							case 0:
								paused = false;
								break;
							case 1:
								AudioManager::setEnableSound(AudioManager::getEnableSound() == false);
								globalAudio->playSound(0);
								pauseMenu->getButtons()[1]->setText("Sound off");
								if (AudioManager::getEnableSound()) {
									mainMenu->getButtons()[1]->setText("Sound On");
									pauseMenu->getButtons()[1]->setText("Sound On");
								}
								else {
									mainMenu->getButtons()[1]->setText("Sound Off");
									pauseMenu->getButtons()[1]->setText("Sound Off");
								}
								break;
							case 2:
								paused = false;
								currentState = MAIN_MENU;
								globalAudio->playSound(0);
								break;
							}
							break;
						}
						case GAME_OVER:
						{
							int clickedButton = gameOverMenu->isIn(mousePos);
							switch (clickedButton) {
							case 0:
								globalAudio->playSound(0);
								snakeGame->reset();
								currentState = IN_GAME;
								break;
							case 1:
								currentState = QUITTING_GAME;
								break;
							}
							break;
						}
						}
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