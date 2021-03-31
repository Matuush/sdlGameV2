#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile() = default;
	Projectile(Vector2D p_position, Vector2D destination) : Entity(){
		init();
		position = p_position;
		currentFrame = { 0, 0, BULLET_TEXTURE.width, BULLET_TEXTURE.height };
		textureID = BULLET_TEXTURE.id;
		colliders.push_back(RectangleCollider(position.x + SCALE, position.y, 2 * SCALE, 4 * SCALE));
		colliders.push_back(RectangleCollider(position.x, position.y + SCALE, 4 * SCALE, 2 * SCALE));
		Entity::entities.push_back(this);
		velocity = destination - position;
		velocity.limit(terminalVelocity);
	}

private:
	void update() override {
		updatePosition();
		if (position.x < 0 || position.y < 0 || position.x > MAP_SIZE.x || position.y > MAP_SIZE.y) {
			Entity::entities.erase(std::remove(Entity::entities.begin(), Entity::entities.end(), this), Entity::entities.end());
			delete this;
		}
	}
	void input(SDL_Event* event) override {}
};