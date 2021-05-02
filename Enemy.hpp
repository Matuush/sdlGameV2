#pragma once
#include "Player.h"


class Enemy : public Entity {
public:
	double health = DEFAULT_ENEMY_HEALTH, damage = DEFAULT_ENEMY_DAMAGE;

	Enemy() = default;
	Enemy(Vector2D p_position) : Entity(p_position, ENEMY_TEXTURE) {
		terminalVelocity = DEFAULT_ENEMY_TERMINAL_VELOCITY;
		solid = true;
		colliders.colliders = kapustaColliders.colliders;
	}

protected:
	inline void changeSprite() {
		lastRight = velocity.x < 0 ? false : (velocity.x > 0 ? true : lastRight);
		int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
		currentFrame = tick == 5 ? SDL_Rect {0, RAW_ENEMY, currentFrame.w, currentFrame.h} : SDL_Rect {tick* RAW_ENEMY, 0, currentFrame.w, currentFrame.h};
	}
	inline void findPlayer() {
		Player* closestPlayer = NULL;
		if (Player::players.size() > 0) {
			for (Player* p : Player::players)
				if (!closestPlayer || abs((p->position - position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2).getMagnitude()) < abs((closestPlayer->position - position + PLAYER_TEXTURE.width / 2 - ENEMY_TEXTURE.width * 2).getMagnitude())) closestPlayer = p;
			velocity = closestPlayer->position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2 - position;
		}
		else velocity = MAP_SIZE / 2 - position;
	}
	void update() override{
		findPlayer();
		updatePosition();
		//changeSprite();
	}
	void input(SDL_Event* event) override { }
};