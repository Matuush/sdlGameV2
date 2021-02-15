#pragma once
#include <vector>
#include <SDL.h>

#include "Entity.h"
#include "Player.h"

#include "Constants.h"

struct Camera : public Entity {
	double x = 0, y = 0, w = screenWidth, h = screenHeight;

	Camera();

	void refresh();

	void update() override;
};