#pragma once
#include <vector>
#include <SDL.h>
#include <iostream>

#include "Vector2D.h"
#include "RectangleCollider.h"

#include "Constants.h"

struct Entity {
	static std::vector<Entity*> entities;

	SDL_Rect currentFrame;
	int textureID;

	Vector2D position, velocity, acceleration;
	double terminalVelocity = defaultTerminalVelocity;
	bool lastRight = 1;

	std::vector<RectangleCollider> colliders;
	bool solid = 0;

	Entity() = default;
	Entity(Vector2D p_position, Texture p_texture);
	Entity(Vector2D p_position, RectangleCollider p_collider, Texture p_texture);
	Entity(Vector2D p_position);

	virtual void update();
	static void updateAll();

	virtual void input(SDL_Event* event);
	static void inputAll(SDL_Event* event);

	bool collides(Entity* second);
protected:
	inline void init();
	inline void updatePosition();
};