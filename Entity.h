#pragma once
#include <SDL.h>

#include "Constants.h"

class Entity {
public:
	bool lastRight = 1;
	Entity();
	Entity(float p_x, float p_y, const int p_id);
	Entity(float p_x, float p_y, const int p_id, int p_w, int p_h);

	void changeTextureID(const int p_id);
	void setPos(float p_x, float p_y);

	float getX();
	float getY();
	char getTextureID();
	SDL_Rect* getCurrentFrame();

	SDL_Rect collider;
protected:
	float x, y;
	SDL_Rect currentFrame;
	int textureID;
};