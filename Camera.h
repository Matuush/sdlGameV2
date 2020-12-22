#pragma once
#include <SDL.h>

#include "Player.h"
#include "Constants.h"

struct Camera {
	SDL_Rect camera;
	float x = 0, y = 0;

	Camera();
	void move(Player* player);
};