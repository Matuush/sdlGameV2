#pragma once
#include "Projectile.h"
#include "KeyState.h"

class Player : public Entity {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState(), prevKeyState = keyState;
	double health = DEFAULT_PLAYER_HEALTH, damage = DEFAULT_PLAYER_DAMAGE;

	Player() = default;
	Player(Vector2D p_position) : Entity(p_position, PLAYER_TEXTURE) {
		terminalVelocity = PLAYER_TERMINAL_VELOCITY;
		solid = true;
		for (auto& col : kapustaColliders) colliders.push_back(RectangleCollider(position.x + col.x, position.y + col.y, col.w, col.h));
		Player::players.push_back(this);
	}

	void update() override {
		velocity = (velocity + acceleration);
		if (keyState.w != prevKeyState.w) velocity.y += keyState.w ? -PLAYER_VELOCITY : PLAYER_VELOCITY;
		if (keyState.a != prevKeyState.a) velocity.x += keyState.a ? -PLAYER_VELOCITY : PLAYER_VELOCITY;
		if (keyState.s != prevKeyState.s) velocity.y += keyState.s ? PLAYER_VELOCITY : -PLAYER_VELOCITY;
		if (keyState.d != prevKeyState.d) velocity.x += keyState.d ? PLAYER_VELOCITY : -PLAYER_VELOCITY;

		velocity.limit(terminalVelocity);

		updatePosition();
		prevKeyState = keyState;

		changeSprite();
	}
	void input(SDL_Event* event) override{
		switch (event->type) {
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym) {
					case SDLK_w: keyState.w = 1; break;
					case SDLK_a: keyState.a = 1; break;
					case SDLK_s: keyState.s = 1; break;
					case SDLK_d: keyState.d = 1; break;
				}
				break;
			case SDL_KEYUP:
				switch (event->key.keysym.sym) {
					case SDLK_w: keyState.w = 0; break;
					case SDLK_a: keyState.a = 0; break;
					case SDLK_s: keyState.s = 0; break;
					case SDLK_d: keyState.d = 0; break;
				}
				break;
			}
	} 
	void recoil(Vector2D shotPos) {
		velocity += position - shotPos;
		velocity.limit(PLAYER_VELOCITY);
	}
private:
	double movementAcceleration = PLAYER_VELOCITY;
	Vector2D lastPos;

	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);

		if (velocity == Vector2D(0, 0))
			//currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
			currentFrame.y = 0, currentFrame.x = 0;
		else {
			int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 2;
		}
	}
};