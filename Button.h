#pragma once
#include <functional>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Entity.h"

#include "Constants.h"

struct Button : public Entity {
	double w, h;
	SDL_Color color;
	const char* text;
	bool clicked = 0;
	std::function<void()> efect;

	Button() = default;
	Button(Vector2D p_position, const char* p_text, std::function<void()> p_efect);

	void checkClick(SDL_Event* event);
	void onClick();
};