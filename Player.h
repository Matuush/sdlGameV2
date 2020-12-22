#pragma once
#include "Entity.h"
#include "Constants.h"

struct Player : public Entity {
public:
	int right = 0, left = 0, up = 0, down = 0;
	bool lastRight = 1;

	Player() = default;
	Player(float p_x, float p_y, SDL_Texture* p_texconst);
	void move(SDL_Event* event);
	void handleMove();
};