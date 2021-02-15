#pragma once
#include <vector>
#include <cmath>
#include <math.h>

#include "Entity.h"
#include "KeyState.h"

#include "Constants.h"

struct Player : public Entity {
	static std::vector<Player*> players;

	KeyState keyState, prevKeyState;

	double movementAcceleration = SPEED;
	Vector2D lastPos;

	std::vector<std::vector<Entity*>>* map;

	Player() = default;
	Player(Vector2D p_position, std::vector<std::vector<Entity*>>* p_map);

	void update() override;
	void input(SDL_Event* event) override;

	inline void changeSprite();
};