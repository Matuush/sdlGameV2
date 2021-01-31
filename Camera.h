#pragma once
#include <SDL.h>

#include "Player.h"

#include "Constants.h"

struct Camera {
	double x = 0, y = 0, w = screenWidth, h = screenHeight;

	Camera();
	void move(Player* player);
};