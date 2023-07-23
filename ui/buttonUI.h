#pragma once
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <dataStructures.h>
#include <string>

class ButtonUI {
	Coordinates position;
	std::string text;
	Vector2D<int> size;
	TTF_Font* font;
	int fontSize;
	Vector3D<int> textColour;
	Vector3D<int> outlineColour;
	Vector3D<int> boxColour;
	bool filled;

public:
	ButtonUI(Coordinates p, std::string t, Vector2D<int> s, const char* fontFileName, 
		int fs = 10, Vector3D<int> tc = Vector3D<int>(0, 0, 0), Vector3D<int> oc = Vector3D<int>(0xff, 0xff, 0xff),
		Vector3D<int> bc = Vector3D<int>(0xff, 0xff, 0xff), bool f = true);

	void render(SDL_Renderer* renderer);

	Coordinates getPosition() { return position; };
	std::string getText() { return text; };
	Vector2D<int> getSize() { return size; };
	TTF_Font* getFont() { return font; };
	int getFontSize() { return fontSize; };
	Vector3D<int> getTextColour() { return textColour; };
	Vector3D<int> getOutlineColour() { return outlineColour; };
	Vector3D<int> getBoxColour() { return boxColour; };
	bool isfilled() { return filled; };

	void setPosition(Coordinates p) { position = p; };
	void setText(std::string t) { text = t; };
	void setSize(Vector2D<int> s) { size = s; };
	void setFont(TTF_Font* f) { font = f; };
	void setFontSize(int fs) { fontSize = fs; };
	void setTextColour(Vector3D<int> tc) { textColour = tc; };
	void setOutlineColour(Vector3D<int> oc) { outlineColour = oc; };
	void setBoxColour(Vector3D<int> bc) { boxColour = bc; };
	void setFilled(bool f) { filled = f; };
};