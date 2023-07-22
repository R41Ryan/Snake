#include "buttonUI.h"

ButtonUI::ButtonUI(Coordinates p, std::string t, Vector2D<int> s)
{
	position = p;
	text = t;
	size = s;
}

void ButtonUI::render(SDL_Renderer* renderer)
{
}
