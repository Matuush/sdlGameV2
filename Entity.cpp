#include "Entity.h"
#include <SDL.h>

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex) : x(p_x), y(p_y), tex(p_tex) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	collider.x = (int)x;
	collider.y = (int)y;
	collider.w = currentFrame.w;
	collider.h = currentFrame.h;
}

float Entity::getX() { return x; }

float Entity::getY() { return y; }

SDL_Texture* Entity::getTexture() { return tex; }

SDL_Rect* Entity::getCurrentFrame() { return &currentFrame; }
