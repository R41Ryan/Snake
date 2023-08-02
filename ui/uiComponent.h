#pragma once
#include <dataStructures.h>
#include <SDL_render.h>

class UIComponent {
	Coordinates position;
	Vector2D<int> size;

public:
	UIComponent(Coordinates p, Vector2D<int> s) {
		position = p;
		size = s;
	}

	virtual void update(Coordinates mousePos) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	Coordinates getPosition() { return position; }
	Vector2D<int> getSize() { return size; }

	void setPosition(Coordinates p) { position = p; }
	void setSize(Vector2D<int> s) { size = s; }
};