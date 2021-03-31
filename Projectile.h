#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile() = default;
	Projectile(Vector2D p_position, Vector2D destination) : Entity(p_position, BULLET_TEXTURE){
		colliders.push_back(RectangleCollider(1, 0, 2, 4));
		colliders.push_back(RectangleCollider(0, 1, 4, 2));
		velocity = destination - position;
		velocity.limit(terminalVelocity);
	}

private:
	void update() override {
		position += velocity;
		if (position.x < 0 || position.y < 0 || position.x > MAP_SIZE.x || position.y > MAP_SIZE.y) {
			Entity::entities.erase(std::remove(Entity::entities.begin(), Entity::entities.end(), this), Entity::entities.end());
			delete this;
		}
	}
	void input(SDL_Event* event) override {}
};