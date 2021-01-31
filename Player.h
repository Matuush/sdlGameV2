#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>

#include "Entity.h"

#include "Constants.h"

struct Player : public Entity {
	int right = 0, left = 0, up = 0, down = 0;
	Vector2D lastPos;
	std::vector<std::vector<Entity>>* map;

	Player() = default;
	Player(Vector2D p_position, std::vector<std::vector<Entity>>* p_map);

	void changeSprite();

	void move(SDL_Event* event);
	void handleMove();
	void stopMomentum();

	inline void revertMove(bool h_x, bool h_y);
};