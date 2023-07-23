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

void ButtonUI::render(SDL_Renderer* renderer)
{
	// Render box

	// Render outline

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
	SDL_Rect textRect{ position.x, position.y, surf->w, surf->h };
	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	TTF_CloseFont(ttfFont);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}
