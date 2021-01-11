#pragma once
#include <SDL.h>

#include "Entity.h"

#include "Constants.h"

struct Button : public Entity {
	const char* text;
	bool clicked = 0;
	char change;

	Button() = default;
	Button(int p_x, int p_y, const char* p_text, const char p_change);

	void checkClick(SDL_Event* event);
	void onClick(char* subject);
};