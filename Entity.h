#pragma once
#include <SDL.h>

class Entity {
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	float getX();
	float getY();
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
private:
	double x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};