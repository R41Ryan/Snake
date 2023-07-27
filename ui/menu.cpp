#include "menu.h"

Menu::Menu(int x, int y, int w, int h, Vector3D<int> oc, Vector3D<int> bc)
{
	position.x = x;
	position.y = y;
	size.a = w;
	size.b = w;
	outlineColour = oc;
	boxColour = bc;
}

Menu::~Menu()
{
	for (int i = 0; i < buttons.size(); i++) {
		delete buttons[i];
	}
	buttons.clear();
}

void Menu::update(Coordinates mousePosition)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update(mousePosition);
	}
}

void Menu::render(SDL_Renderer* renderer)
{
	// Render the box of the menu first
	SDL_Rect renderRect{ position.x - size.a / 2, position.y - size.b / 2, size.a, size.b };
	SDL_SetRenderDrawColor(renderer, boxColour.a, boxColour.b, boxColour.c, 0xff);
	SDL_RenderFillRect(renderer, &renderRect);
	SDL_SetRenderDrawColor(renderer, outlineColour.a, outlineColour.b, outlineColour.c, 0xff);
	SDL_RenderDrawRect(renderer, &renderRect);

	// Render the menu buttons, re-adjusting their position as needed
	repositionButtons();
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render(renderer);
	}
}

void Menu::reset()
{
}

void Menu::addButton(ButtonUI* button)
{
	buttons.push_back(button);
	repositionButtons();
}

void Menu::repositionButtons()
{
	int count = buttons.size();
	int verticalSpacing = size.b / (count + 1);
	for (int i = 0; i < count; i++) {
		Vector2D<int> buttonSize = buttons[i]->getSize();
		buttons[i]->setPosition(Coordinates(position.x, position.y - size.a / 2 + (i + 1) * verticalSpacing));
	}
}

int Menu::isIn(Coordinates mousePosition)
{
	int toReturn = -1;
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isIn(mousePosition)) {
			toReturn = i;
		}
	}
	return toReturn;
}
