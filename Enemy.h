#pragma once
#include "Player.h"


class Enemy : public Entity {
public:
	double health = DEFAULT_ENEMY_HEALTH, damage = DEFAULT_ENEMY_DAMAGE;

	Enemy() = default;
	Enemy(Vector2D p_position) : Entity() {
		init();
		position = p_position;

		currentFrame = { 0, 0, ENEMY_TEXTURE.width , ENEMY_TEXTURE.height }, textureID = ENEMY_TEXTURE.id;

		solid = true;
		for (auto& col : kapustaColliders)
			colliders.push_back(RectangleCollider(position.x + col.x, position.y + col.y, col.w, col.h));

		Entity::entities.push_back(this);
	}

protected:
	inline void changeSprite() {
		if (velocity.x < 0) lastRight = false;
		else if (velocity.x > 0) lastRight = true;

		// Change later
		int tick = (int)(SDL_GetTicks() / (500 / PLAYER_VELOCITY)) % 6;
		if (tick == 5) currentFrame.y = RAW_PLAYER, currentFrame.x = 0;
		else currentFrame.y = 0, currentFrame.x = tick * RAW_PLAYER;
	}
	inline void findPlayer() {
		Player* closestPlayer = NULL;
		if (Player::players.size() > 0) {
			for (Player* p : Player::players)
				if (!closestPlayer || abs((p->position - position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2).getMagnitude()) < abs((closestPlayer->position - position + PLAYER_TEXTURE.width / 2 - ENEMY_TEXTURE.width * 2).getMagnitude()))
					closestPlayer = p;
			velocity = closestPlayer->position + PLAYER_TEXTURE.width * 2 - ENEMY_TEXTURE.width * 2 - position;
		}
		else velocity = MAP_SIZE / 2 - position;
		velocity.limit(DEFAULT_ENEMY_TERMINAL_VELOCITY);
	}
	void update() override{
		findPlayer();
		updatePosition();
		//changeSprite();
	}
	void input(SDL_Event* event) override { }
};

