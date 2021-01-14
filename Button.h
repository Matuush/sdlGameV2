#pragma once
#include <iostream>
#include <functional>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Entity.h"

#include "Constants.h"

struct Button : public Entity {
	TTF_Font* font;
	SDL_Color color;
	const char* text;
	bool clicked = 0;
	std::function<void()> efect;

	Button() = default;
	Button(int p_x, int p_y, const char* p_text, std::function<void()> p_efect);

	void checkClick(SDL_Event* event);
	void onClick();
};