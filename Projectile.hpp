#pragma once
#include "Entity.hpp"

class Projectile : public Entity {
public:
	Projectile() = default;
	Projectile(Vector2D p_position, Vector2D destination) : Entity(){
		init();
		terminalVelocity = DEFAULT_BULLET_TERMINAL_VELOCITY;
		position = p_position;
		currentFrame = { 0, 0, BULLET_TEXTURE.width, BULLET_TEXTURE.height };
		textureID = BULLET_TEXTURE.id;
		colliders.colliders.push_back(new Collider(position + BULLET_TEXTURE.width * SCALE / 2, BULLET_WIDTH));
		Entity::entities.push_back(this);
		velocity = destination - position;
		velocity.setMagnitude(terminalVelocity);
	}
private:
	void update() override {
		updatePosition();
		if (position.x < 0 || position.y < 0 || position.x > MAP_SIZE.x || position.y > MAP_SIZE.y || velocity < 5) delete this;
	}
	void input(SDL_Event* event) override {}
};