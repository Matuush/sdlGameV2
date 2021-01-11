#include "Button.h"

#include <iostream>

Button::Button(int p_x, int p_y, const char* p_text) : text(p_text){
	collider.x = p_x;
	collider.y = p_y;
	collider.w = 100;
	collider.h = 50;

	currentFrame.x = 1;
	currentFrame.y = 1;
	currentFrame.w = 2;
	currentFrame.h = 1;
	
	textureID = 0;
}

void Button::onClick() {
	std::cout << "Button\n";
}