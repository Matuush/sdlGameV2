#pragma once
#include <SDL.h>

#include "Constants.h"

class Entity {
public:
	SDL_Rect collider;

	Entity() = default;
	Entity(float p_x, float p_y, SDL_Texture* p_tex);

	float getX();
	float getY();
	SDL_Texture* getTexture();
	SDL_Rect* getCurrentFrame();
protected:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};