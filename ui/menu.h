#pragma once
#include "buttonUI.h"
#include <dataStructures.h>
#include <vector>

class Menu {
	Coordinates position;
	Vector2D<int> size;
	std::vector<ButtonUI*> buttons;
	Vector3D<int> outlineColour;
	Vector3D<int> boxColour;

public:
	Menu(int x = 0, int y = 0, int w = 100, int h = 100, 
		Vector3D<int> oc = Vector3D<int>(0xff, 0xff, 0xff), 
		Vector3D<int> bc = Vector3D<int>());
	~Menu();

	void update(Coordinates mousePosition);
	void render(SDL_Renderer* renderer);
	void reset();

	void addButton(ButtonUI* button);
	// Moves and resizes the buttons as appropriate
	void adjustButtons();
	// Returns the index of the button that the mouseCoordinate is in
	int isIn(Coordinates mousePosition);

	Coordinates getPosition() { return position; };
	Vector2D<int> getSize() { return size; };
	std::vector<ButtonUI*> getButtons() { return buttons; };

	void setPosition(Coordinates p) { position = p; };
	void setSize(Vector2D<int> s) { size = s; };
	void setButtons(std::vector<ButtonUI*> b) { buttons = b; };
};