#pragma once
#include "Projectile.h"
#include "KeyState.h"

class Player : public Entity {
public:
	static std::vector<Player*> players;

	KeyState keyState = KeyState(), prevKeyState = keyState;
	double health = DEFAULT_PLAYER_HEALTH, damage = DEFAULT_PLAYER_DAMAGE;
	Vector2D* cameraPos;

	Player() = default;
	Player(Vector2D p_position, Vector2D* p_cameraPos) : Entity(p_position, PLAYER_TEXTURE), cameraPos(p_cameraPos){
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

		//changeSprite();

		if (keyState.lcPos != DEFAULT_BULLET_POSITION) {
			new Projectile(position + RAW_PLAYER * SCALE / 2, keyState.lcPos);
			keyState.lcPos = DEFAULT_BULLET_POSITION;
		}
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
			case SDL_MOUSEBUTTONDOWN:
				keyState.lcPos = Vector2D(event->button.x, event->button.y) + *cameraPos;
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
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);

		if (((keyState.a == 0 && keyState.d == 0) || (keyState.a == 1 && keyState.d == 1)) && ((keyState.w == 0 && keyState.s == 0) || (keyState.w == 1 && keyState.s == 1))) 
			currentFrame.y = RAW_PLAYER, currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * RAW_PLAYER;
		else {
			int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
			currentFrame = tick == 5 ? SDL_Rect{ 0, RAW_ENEMY, currentFrame.w, currentFrame.h } : SDL_Rect{ tick * RAW_ENEMY, 0, currentFrame.w, currentFrame.h };
		}
	}

private:
	double movementAcceleration = PLAYER_VELOCITY;
	Vector2D lastPos;
};