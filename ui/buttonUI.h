#pragma once
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <dataStructures.h>
#include <control/audioManager.h>
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
	Vector3D<int> highlightColour;
	bool filled;
	bool hovered;
	
	AudioManager* audio;

public:
	ButtonUI(Coordinates p, std::string t, Vector2D<int> s, const char* fontFileName, 
		int fs = 10, Vector3D<int> tc = Vector3D<int>(0, 0, 0), Vector3D<int> oc = Vector3D<int>(0xff, 0xff, 0xff),
		Vector3D<int> bc = Vector3D<int>(0xff, 0xff, 0xff), Vector3D<int> hc = Vector3D<int>(0x88, 0x88, 0x88), bool f = true);
	~ButtonUI();

	void update(Coordinates mousePos);
	void render(SDL_Renderer* renderer);
	bool isIn(Coordinates pos);
	// Checks if the mouse coordinates hover over the mouse and changes hovered as appropriate.
	// Returns a bool for if there was a change of state in hovered.
	bool checkHover(Coordinates mousePos);

	Coordinates getPosition() { return position; };
	std::string getText() { return text; };
	Vector2D<int> getSize() { return size; };
	TTF_Font* getFont() { return font; };
	int getFontSize() { return fontSize; };
	Vector3D<int> getTextColour() { return textColour; };
	Vector3D<int> getOutlineColour() { return outlineColour; };
	Vector3D<int> getBoxColour() { return boxColour; };
	Vector3D<int> getHighlightColour() { return highlightColour; };
	bool isfilled() { return filled; };
	bool isHovered() { return hovered; };
	AudioManager* getAudio() { return audio; };

	void setPosition(Coordinates p) { position = p; };
	void setText(std::string t) { text = t; };
	void setSize(Vector2D<int> s) { size = s; };
	void setFont(TTF_Font* f) { font = f; };
	void setFontSize(int fs) { fontSize = fs; };
	void setTextColour(Vector3D<int> tc) { textColour = tc; };
	void setOutlineColour(Vector3D<int> oc) { outlineColour = oc; };
	void setBoxColour(Vector3D<int> bc) { boxColour = bc; };
	void setHightlightColour(Vector3D<int> hc) { highlightColour = hc; };
	void setFilled(bool f) { filled = f; };
	void setHovered(bool h) { hovered = h; };
	void setAudio(AudioManager* a) { audio = a; };
};