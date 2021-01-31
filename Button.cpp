#include "Button.h"

#include <iostream>

Button::Button(Vector2D p_position, const char* p_text, std::function<void()> p_efect) : text(p_text), efect(p_efect){
	// Setup for text
	font = TTF_OpenFont("textures/Sans.ttf", 24);
	color = {0, 0, 0};

	position = p_position;
	w = buttonWidth;
	h = buttonHeight;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = rawTile * 2;
	currentFrame.h = rawTile;

	textureID = buttonTexture.id;
}

void Button::checkClick(SDL_Event* event) {
	if ((event->button.x > position.x) && (event->button.x < position.x + w) &&
		(event->button.y > position.y) && (event->button.y < position.y + h)) {
		color = { 50, 50, 50 };
		currentFrame.y = 32;
		if (event->button.button == SDL_BUTTON_LEFT && event->type == SDL_MOUSEBUTTONDOWN) clicked = 1;
	}
	else {
		color = { 0, 0, 0 };
		currentFrame.y = 0;
	}
}

void Button::onClick() {
	if (clicked) {
		efect();
		clicked = 0;
	}
}