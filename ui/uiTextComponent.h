#pragma once
#include "uiComponent.h"
#include <SDL_ttf.h>

class UITextComponent : public UIComponent {
	std::string text;
	TTF_Font* font;
	int fontSize;
	Vector3D<int> textColour;

public:
	UITextComponent(Coordinates p, Vector2D<int> s, std::string t, const char* fontFileName,
		int fs = 10, Vector3D<int> tc = Vector3D<int>(0, 0, 0)) : UIComponent(p, s) {
		text = t;
		font = TTF_OpenFont(fontFileName, fs);
		if (font == nullptr)
		{
			std::cout << "Error opening font for ButttonUI. TTF_ERROR: " << TTF_GetError() << std::endl;
			return;
		}
		fontSize = fs;
		textColour = tc;
	}
	virtual ~UITextComponent() {
		TTF_CloseFont(font);
	}

	virtual void update(Coordinates mousePos) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	std::string getText() { return text; }
	TTF_Font* getFont() { return font; }
	int getFontSize() { return fontSize; }
	Vector3D<int> getTextColour() { return textColour; }

	void setText(std::string t) { text = t; }
	void setFont(TTF_Font* f) { font = f; }
	void setFontSize(int fs) { fontSize = fs; }
	void setTextColour(Vector3D<int> tc) { textColour = tc; }
};