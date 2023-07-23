#include "buttonUI.h"
#include <iostream>

ButtonUI::ButtonUI(Coordinates p, std::string t, Vector2D<int> s, const char* fontFileName, int fs, 
	Vector3D<int> tc, Vector3D<int> oc, Vector3D<int> bc, bool f)
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
	filled = f;
}

ButtonUI::~ButtonUI()
{
	TTF_CloseFont(font);
}

void ButtonUI::render(SDL_Renderer* renderer)
{
	SDL_Rect boxRect{ position.x - size.a / 2, position.y - size.b / 2, size.a, size.b };
	// Render box
	if (filled) {
		SDL_SetRenderDrawColor(renderer, boxColour.a, boxColour.b, boxColour.c, 0xff);
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
