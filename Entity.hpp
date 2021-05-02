#pragma once
#include "SDL2/SDL.h"
#include "Constants.hpp"
#include <iostream>

class Entity {
public:
	static std::vector<Entity*> entities;

	SDL_Rect currentFrame = {0, 0, RAW_TILE, RAW_TILE};
	unsigned char textureID = NOTHING_TEXTURE.id;
	bool lastRight = true, display = true;

	Vector2D position;
	MultiCollider colliders;
	bool solid = 0;

	Entity() { init(); }
	Entity(Vector2D p_position, Texture p_texture) : position(p_position), textureID(p_texture.id) {
		init();
		currentFrame = { 0, 0, p_texture.width, p_texture.height };
		if (textureID != ENEMY_TEXTURE.id && textureID != PLAYER_TEXTURE.id) colliders.colliders.push_back(new Collider(position, { TILE_SIZE, TILE_SIZE }));
		Entity::entities.push_back(this);
	}
	Entity(Vector2D p_position, Collider p_collider, Texture p_texture) : position(p_position), textureID(p_texture.id) {
		init();
		currentFrame = { 0, 0, p_texture.width, p_texture.height };
		colliders.colliders.push_back(&p_collider);
		Entity::entities.push_back(this);
	}
	~Entity() {
		Entity::entities.erase(std::remove(Entity::entities.begin(), Entity::entities.end(), this), Entity::entities.end());
	}
	static void updateAll() {
		for (auto&& e : Entity::entities) e->update();
	}
	static void inputAll(SDL_Event* event) {
		for (auto&& e : Entity::entities)
			if(e) e->input(event);
	}
	bool collides(Entity* second) {
		return colliders.collides(&second->colliders);
	}

protected:
	Vector2D velocity, acceleration;
	double terminalVelocity = DEFAULT_TERMINAL_VELOCITY;

	inline void init() {
		acceleration = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		colliders;
	}

	inline bool collisionOnMovement(Vector2D vel) {
		bool axisCollides = false;
		colliders.move(vel);
		for (Entity* e : Entity::entities) {
			if (!e->solid || e == this) continue;
			else if (colliders.collides(&e->colliders)) {
				axisCollides = true;
				break;
			}
		}
		colliders.move(Vector2D(0, 0) - vel);
		return axisCollides;
	}

	inline void updatePosition() {
		velocity.limit(terminalVelocity);

		const Vector2D pp = position;

		if (solid) {
			if (!collisionOnMovement({ velocity.x, 0.0 })) position.x += velocity.x;
			if (!collisionOnMovement({ 0.0, velocity.y })) position.y += velocity.y;
		}
		else position += velocity;

		colliders.move(position - pp);

		velocity *= 1 - FRICTION;
		if (velocity.getMagnitude() < 0.5) velocity = 0;
	}
	
	virtual void update() {
		updatePosition();
	}

	virtual void input(SDL_Event* event) {
	
	}
};