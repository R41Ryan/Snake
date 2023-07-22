#pragma once
#include <SDL.h>
#include <SDL_render.h>
#include <dataStructures.h>
#include <string>

class ButtonUI {
	Coordinates position;
	std::string text;
	Vector2D<int> size;

public:
	ButtonUI(Coordinates p, std::string t, Vector2D<int> s);

	void render(SDL_Renderer* renderer);

	Coordinates getPosition() { return position; };
	std::string getText() { return text; };
	Vector2D<int> getSize() { return size; };

	void setPosition(Coordinates p) { position = p; };
	void setText(std::string t) { text = t; };
	void setSize(Vector2D<int> s) { size = s; };
};