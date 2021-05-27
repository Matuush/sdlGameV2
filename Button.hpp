#pragma once
#include <functional>
#include "SDL2/SDL_ttf.h"
#include "Entity.hpp"

class Button{
public:
	bool unlocked;
	double w = BUTTON_SIZE.x, h = BUTTON_SIZE.y;
	SDL_Color color = PASSIVE_BUTTON_TEXT_COLOR;
	const char* text;
	Vector2D position;
	Texture texture = BUTTON_TEXTURE;
	SDL_Rect currentFrame = { 0, 0, texture.width, texture.height };

	Button() = default;
	Button(Vector2D p_position, const char* p_text, std::function<void()> p_efect, bool p_unlocked = true) : 
		text(p_text), efect(p_efect), position(p_position), unlocked(p_unlocked) {}

	void checkClick(SDL_Event* event) {
		if ((event->button.x > position.x) && (event->button.x < position.x + w) &&
			(event->button.y > position.y) && (event->button.y < position.y + h)) {
			color = ACTIVE_BUTTON_TEXT_COLOR;
			currentFrame.y = texture.height;
			if (event->button.button == SDL_BUTTON_LEFT && event->type == SDL_MOUSEBUTTONDOWN ) {
				if(unlocked) clicked = true;
				else color = LOCKED_BUTTON_TEXT_COLOR;
			}
		}
		else {
			color = PASSIVE_BUTTON_TEXT_COLOR;
			currentFrame.y = 0;
		}
	}
	void onClick() {
		if (clicked) {
			efect();
			clicked = false;
		}
	}

private:
	bool clicked = false;
	std::function<void()> efect;
};