#include "buttonUI.h"
#include <iostream>

ButtonUI::ButtonUI(Coordinates p, std::string t, Vector2D<int> s, const char* fontFileName, int fs, 
	Vector3D<int> tc, Vector3D<int> oc, Vector3D<int> bc, Vector3D<int> hc, bool f)
{
	position = p;
	text = t;
	size = s;
	font = TTF_OpenFont(fontFileName, fs);
	if (font == nullptr)
	{
		std::cout << "Error opening font for ButttonUI. TTF_ERROR: " << TTF_GetError() << std::endl;
		return;
	}
	fontSize = fs;
	textColour = tc;
	outlineColour = oc;
	boxColour = bc;
	highlightColour = hc;
	filled = f;
	hovered = false;
	playing = -1;
}

ButtonUI::~ButtonUI()
{
	TTF_CloseFont(font);
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] != nullptr)
			Mix_FreeChunk(sounds[i]);
	}
}

void ButtonUI::render(SDL_Renderer* renderer)
{
	SDL_Rect boxRect{ position.x - size.a / 2, position.y - size.b / 2, size.a, size.b };
	// Render box
	if (filled) {
		if (hovered)
		{
			SDL_SetRenderDrawColor(renderer, highlightColour.a, highlightColour.b, highlightColour.c, 0xff);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, boxColour.a, boxColour.b, boxColour.c, 0xff);
		}
		SDL_RenderFillRect(renderer, &boxRect);
	}

	// Render outline

	SDL_SetRenderDrawColor(renderer, outlineColour.a, outlineColour.b, outlineColour.c, 0xff);
	SDL_RenderDrawRect(renderer, &boxRect);

	// Render text
	SDL_Color colour = { textColour.a, textColour.b, textColour.c, 0xFF };
	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), colour);
	if (surf == nullptr)
	{
		std::cout << "Error converting font to surface. TTF_ERROR: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
	{
		SDL_FreeSurface(surf);
		std::cout << "Error converting surface to texture. SDL_ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_Rect textRect{ position.x - surf->w / 2, position.y - surf->h / 2, surf->w, surf->h };
	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

bool ButtonUI::isIn(Coordinates pos)
{
	int leftBoundary = position.x - size.a / 2;
	int rightBoundary = position.x + size.a / 2;
	int topBoundary = position.y - size.b / 2;
	int bottomBoundary = position.y + size.b / 2;

	if (pos.x < leftBoundary || pos.x > rightBoundary || pos.y < topBoundary || pos.y > bottomBoundary)
	{
		return false;
	}

	return true;
}

void ButtonUI::update(Coordinates mousePos)
{
	bool changedHoverdState = checkHover(mousePos);
	if (changedHoverdState)
	{
		playSound(0);
	}

	if (playing >= 0)
	{
		Mix_PlayChannel(-1, sounds[playing], 0);
		playing = -1;
	}
}

bool ButtonUI::checkHover(Coordinates mousePos)
{
	bool changedState = false;
	if (isIn(mousePos))
	{
		if (hovered == false)
			changedState = true;
		hovered = true;
	}
	else
	{
		if (hovered == true)
			changedState = true;
		hovered = false;
	}
	return changedState;
}

void ButtonUI::loadSound(const char* sound, int index)
{
	if (index < 0 || index >= MAX_SOUNDS)
	{
		std::cout << "Error loading sound: index is out of bounds.\n";
		return;
	}
	if (sounds[index] != nullptr)
		Mix_FreeChunk(sounds[index]);
	sounds[index] = Mix_LoadWAV(sound);
	if (sounds[index] == nullptr)
	{
		std::cout << "Error loading sound: Invalid file path.\n";
	}
}

void ButtonUI::playSound(int index)
{
	if (index < 0 || index >= MAX_SOUNDS)
	{
		std::cout << "Error playing sound: index is out of bounds.\n";
		return;
	}
	if (sounds[index] == nullptr)
	{
		std::cout << "Error playing sound: sound index is null.\n";
		return;
	}
	if (sounds[index] != nullptr && playing < 0)
		playing = index;
}
