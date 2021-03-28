#pragma once
#include "Entity.h"
#include "KeyState.h"

class Player : public Entity {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState(), prevKeyState;
	double health = DEFAULT_PLAYER_HEALTH, damage = DEFAULT_PLAYER_DAMAGE;

	Player() = default;
	Player(Vector2D p_position) : Entity() {
		position = p_position, lastPos = position;
		terminalVelocity = PLAYER_TERMINAL_VELOCITY;

		currentFrame = { 0, 0, PLAYER_TEXTURE.width, PLAYER_TEXTURE.height }, textureID = PLAYER_TEXTURE.id;

		solid = true;
		for (auto& col : kapustaColliders)
			colliders.push_back(RectangleCollider(position.x + col.x, position.y + col.y, col.w, col.h));

		Player::players.push_back(this);
		Entity::entities.push_back(this);
	}

	void update() override {
		velocity = (velocity + acceleration);
		if (keyState.w != prevKeyState.w) {
			if (keyState.w) velocity.y -= PLAYER_VELOCITY;
			else velocity.y += PLAYER_VELOCITY;
		}
		if (keyState.a != prevKeyState.a) {
			if (keyState.a) velocity.x -= PLAYER_VELOCITY;
			else velocity.x += PLAYER_VELOCITY;
		}
		if (keyState.s != prevKeyState.s) {
			if (keyState.s) velocity.y += PLAYER_VELOCITY;
			else velocity.y -= PLAYER_VELOCITY;
		}
		if (keyState.d != prevKeyState.d) {
			if (keyState.d) velocity.x += PLAYER_VELOCITY;
			else velocity.x -= PLAYER_VELOCITY;
		}

		velocity.limit(terminalVelocity);

		updatePosition();
		prevKeyState = keyState;

		//changeSprite();
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

	inline void changeSprite() {
		if (velocity.x < 0) lastRight = true;
		else if (velocity.x > 0) lastRight = false;

		if (((keyState.a == 0 && keyState.d == 0) || (keyState.a == 1 && keyState.d == 1)) && ((keyState.w == 0 && keyState.s == 0) || (keyState.w == 1 && keyState.s == 1))) 
			currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
		else {
			int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
			if (tick != 5) currentFrame.y = 0, currentFrame.x = tick * RAW_PLAYER;
			else currentFrame.y = RAW_PLAYER, currentFrame.x = 0;
		}
	}

private:
	double movementAcceleration = PLAYER_VELOCITY;
	Vector2D lastPos;
};