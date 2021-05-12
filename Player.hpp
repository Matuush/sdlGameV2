#pragma once
#include "Projectile.hpp"
#include "data/KeyState.hpp"

class Player : public Entity {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState();
	double health = DEFAULT_PLAYER_HEALTH, damage = DEFAULT_PLAYER_DAMAGE;

	Player() = default;
	Player(Vector2D p_position) : Entity(p_position, PLAYER_TEXTURE) {
		terminalVelocity = PLAYER_TERMINAL_VELOCITY;
		solid = true;
		colliders.add(new Collider(position + PLAYER_TEXTURE.width * SCALE / 2, 248));
		Player::players.push_back(this);
	}

	void update() override {
		velocity.y += keyState.w ? -movementAcceleration / 10 : movementAcceleration / 10;
		velocity.x += keyState.a ? -movementAcceleration / 10 : movementAcceleration / 10;
		velocity.y += keyState.s ? movementAcceleration / 10 : -movementAcceleration / 10;
		velocity.x += keyState.d ? movementAcceleration / 10 : -movementAcceleration / 10;

		updatePosition();

		changeSprite();
	}
	void input(SDL_Event* event) override{
		keyState.update(event);
	}
	void shoot(SDL_Event* event, Vector2D camPos){
		Vector2D shotPos = Vector2D(event->button.x + camPos.x, event->button.y + camPos.y);
		new Projectile(position + RAW_PLAYER * SCALE / 2, shotPos); 
		recoil(shotPos);
	}
private:
	double movementAcceleration = PLAYER_VELOCITY;
	Vector2D lastPos;

	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);

		if (velocity < 1) currentFrame.y = 0, currentFrame.x = 0;
			//currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
		else {
			int tick = (int)(SDL_GetTicks() / (7000 / velocity.getMagnitude())) % 2;
			currentFrame.x = PLAYER_TEXTURE.width * tick;
		}
	}

	inline void recoil(Vector2D shotPos) {
		Vector2D tAcceleration = (position + PLAYER_TEXTURE.width / 2 * SCALE) - shotPos;
		tAcceleration.limit(movementAcceleration * 3);
		velocity += tAcceleration;
	}
};