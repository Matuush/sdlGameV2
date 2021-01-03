#pragma once
#include <SDL.h>

#include "Player.h"

#include "Constants.h"

struct Camera {
	float x = 0, y = 0;
	SDL_Rect camera;

	Camera();
	void move(Player* player);
};