#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile() = default;
	Projectile(Vector2D p_position, Vector2D p_destination) : Entity(p_position, BULLET_TEXTURE), destination(p_destination) {
		colliders.push_back(RectangleCollider(1, 0, 2, 4));
		colliders.push_back(RectangleCollider(0, 1, 4, 2));
		velocity = destination - position;
		velocity.limit(terminalVelocity);
	}

private:
	Vector2D destination;
	void update() override {
		position += velocity;
		if (collides(&Entity::borderWall)) delete this;
	}
	void input(SDL_Event* event) override {}
};