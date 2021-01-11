#include "Button.h"

#include <iostream>

Button::Button(int p_x, int p_y, const char* p_text, const char p_change) : text(p_text), change(p_change){
	collider.x = p_x;
	collider.y = p_y;
	collider.w = 400;
	collider.h = 200;

	currentFrame.x = 1;
	currentFrame.y = 1;
	currentFrame.w = 2;
	currentFrame.h = 1;

}

void Button::checkClick(SDL_Event* event) {
	if ((event->button.x > collider.x) && (event->button.x < collider.x + collider.w) &&
		(event->button.y > collider.y) && (event->button.y < collider.y + collider.h) &&
		(event->type == SDL_MOUSEBUTTONUP)) {
		if(event->button.button == SDL_BUTTON_LEFT) clicked = 1;
	}
}

void Button::onClick(char *subject) {
	if (clicked) {
		std::cout << "h\n";
		*subject = change;

		clicked = 0;
	}
}