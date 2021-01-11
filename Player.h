#pragma once
#include <vector>

#include "Entity.h"

#include "Constants.h"

struct Player : public Entity {
	int right = 0, left = 0, up = 0, down = 0;
	float lastPos[2];

	std::vector<std::vector<Entity>>* map;

	Player() = default;
	Player(float p_x, float p_y, std::vector<std::vector<Entity>>* p_map);

	void changeSprite();

	inline void moveCollider();

	void move(SDL_Event* event);
	void handleMove(SDL_Rect* screen);
	void stopMomentum();

	inline void revertMove(bool h_x, bool h_y);
};