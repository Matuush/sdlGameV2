#pragma once
#include <vector>
#include <SDL.h>

#include "Vector2D.h"
#include "RectangleCollider.h"

#include "Constants.h"

struct Entity {
	static std::vector<Entity*> entities;

	SDL_Rect currentFrame;
	int textureID;
	Vector2D position, velocity, acceleration;
	std::vector<RectangleCollider> colliders;
	bool lastRight = 1;

	Entity();
	Entity(Vector2D p_position, Texture p_texture);
	Entity(Vector2D p_position, RectangleCollider p_collider, Texture p_texture);

	void update();
	static void updateAll();

	bool collides(Entity* second);
};