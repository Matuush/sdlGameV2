#pragma once
#include "Player.h"


class Enemy : public Entity {
public:
	double health = defaultEnemyHealth, damage = defaultEnemyDamage;

	Enemy() = default;
	Enemy(Vector2D p_position) : Entity() {
		init();
		position = p_position;

		currentFrame = { 0, 0, ENEMY_TEXTURE.width , ENEMY_TEXTURE.height };
		textureID = ENEMY_TEXTURE.id;

		solid = true;
		colliders.push_back(RectangleCollider(position + enemyHitboxDistance, enemyHitboxSize));

		Entity::entities.push_back(this);
	}

protected:
	inline void changeSprite() {
		if (velocity.x < 0) lastRight = false;
		else if (velocity.x > 0) lastRight = true;

		// Change later
		int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
		if (tick == 5) {
			currentFrame.y = RAW_PLAYER;
			currentFrame.x = 0;
		}
		else {
			currentFrame.y = 0;
			currentFrame.x = tick * RAW_PLAYER;
		}
	}
	void update() override{
		Player* closestPlayer = NULL;
		bool playerExists = false;
		if (Player::players.size() > 0) {
			for (Player* p : Player::players)
				if (!closestPlayer || abs((p->position - position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2).getMagnitude()) < abs((closestPlayer->position - position + PLAYER_TEXTURE.width / 2 - ENEMY_TEXTURE.width * 2).getMagnitude()))
					closestPlayer = p;
			playerExists = true;
		}
		if (playerExists) velocity = closestPlayer->position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2 - position;
		else velocity = MAP_SIZE / 2 - position;
		velocity.limit(defaultEnemyTerminalVelocity);

		updatePosition();

		//changeSprite();
	}
	void input(SDL_Event* event) override {

	}
};

