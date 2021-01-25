#include "Button.h"

#include <iostream>

Button::Button(int p_x, int p_y, const char* p_text, std::function<void()> p_efect) : text(p_text), efect(p_efect){
	font = TTF_OpenFont("textures/Sans.ttf", 24);
	color = {0, 0, 0};

	collider.x = p_x;
	collider.y = p_y;
	collider.w = buttonWidth;
	collider.h = buttonHeight;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 32;

	textureID = 5;
}

void Button::checkClick(SDL_Event* event) {
	if ((event->button.x > collider.x) && (event->button.x < collider.x + collider.w) &&
		(event->button.y > collider.y) && (event->button.y < collider.y + collider.h)) {
		color = { 50, 50, 50 };
		currentFrame.y = 32;
		if (event->button.button == SDL_BUTTON_LEFT && event->type == SDL_MOUSEBUTTONDOWN) { clicked = 1; }
	}
	else {
		color = { 0, 0, 0 };
		currentFrame.y = 0;
	}
}

void Button::onClick() {
	if (clicked) { // Fortnite
		efect();
		clicked = 0;
	}
}