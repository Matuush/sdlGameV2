#pragma once
#include <SDL.h>

#include "Constants.h"

class Entity {
public:
	SDL_Rect collider;

	Entity() = default;
	Entity(float p_x, float p_y, char p_id);

	void changeTextureID(char p_id);

	float getX();
	float getY();

	void setPos(float p_x, float p_y);

	char getTextureID();
	SDL_Rect* getCurrentFrame();

protected:
	float x, y;
	SDL_Rect currentFrame;
	char id;
};