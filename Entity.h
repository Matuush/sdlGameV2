#pragma once
#include <vector>
#include "SDL/SDL.h"
#include "Constants.h"

class Entity {
public:
	static std::vector<Entity*> entities;

	SDL_Rect currentFrame = {0, 0, RAW_TILE, RAW_TILE};
	int textureID = NOTHING_TEXTURE.id;
	bool lastRight = true;

	Vector2D position;
	std::vector<RectangleCollider> colliders;
	bool solid = 0;

	Entity() { init(); }
	Entity(Vector2D p_position, Texture p_texture) : position(p_position), textureID(p_texture.id) {
		init();
		currentFrame = { 0, 0, p_texture.width, p_texture.height };
		colliders.push_back(RectangleCollider(position.x, position.y, TILE_SIZE, TILE_SIZE));
		Entity::entities.push_back(this);
	}
	Entity(Vector2D p_position, RectangleCollider p_collider, Texture p_texture) : position(p_position), textureID(p_texture.id) {
		init();
		currentFrame = { 0, 0, p_texture.width, p_texture.height };
		colliders.push_back(p_collider);
		Entity::entities.push_back(this);
	}

	static void updateAll() {
		for (auto&& e : Entity::entities)
			e->update();
	}
	static void inputAll(SDL_Event* event) {
		for (auto&& e : Entity::entities)
			e->input(event);
	}

	bool collides(Entity* second) {
		for (RectangleCollider c : colliders)
			for (RectangleCollider cc : second->colliders)
				if (c.collides(&cc)) return true;
		return false;
	}

protected:
	Vector2D velocity, acceleration;
	double terminalVelocity = DEFAULT_TERMINAL_VELOCITY;

	inline void init() {
		acceleration = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		colliders;
	}

	inline void updatePosition() {
		Vector2D pp(position.x, position.y);

		if (solid) {
			bool xCollides = false;
			for (RectangleCollider& c : colliders) {
				c.x += velocity.x;
				for (Entity* e : Entity::entities) {
					if (!e->solid || e == this) continue;
					for (RectangleCollider cc : e->colliders)
						if (c.collides(&cc)) xCollides = true;
					if (xCollides) break;
				}
				c.x -= velocity.x;
				if (xCollides) break;
			}
			if (!xCollides) position.x += velocity.x;

			bool yCollides = false;
			for (RectangleCollider& c : colliders) {
				c.y += velocity.y;
				for (Entity* e : Entity::entities) {
					if (!e->solid || e == this) continue;
					for (RectangleCollider cc : e->colliders)
						if (c.collides(&cc)) yCollides = true;
					if (yCollides) break;
				}
				c.y -= velocity.y;
				if (xCollides) break;
			}
			if (!yCollides) position.y += velocity.y;
		}
		else position = position + velocity;

		Vector2D dif = position - pp;
		for (RectangleCollider& c : colliders)
			c.x += dif.x, c.y += dif.y;
	}
	
	virtual void update() {
		velocity = (velocity + acceleration);
		velocity.limit(terminalVelocity);

		updatePosition();
	}

	virtual void input(SDL_Event* event) { }
};