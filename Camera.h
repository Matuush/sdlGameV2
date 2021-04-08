#pragma once
#include "Player.h"

struct Camera : public Entity {
	double w = SCREEN_SIZE.x, h = SCREEN_SIZE.y;

	Camera() : Entity(Vector2D(0, 0), NOTHING_TEXTURE) {
		display = false;
		colliders = MultiCollider({ 
			new Collider(0, SCREEN_SIZE.y, SCREEN_SIZE.x, BORDER_THICKNESS),
			new Collider(SCREEN_SIZE.x, 0, BORDER_THICKNESS, SCREEN_SIZE.y),
			new Collider(0, -BORDER_THICKNESS, SCREEN_SIZE.x, BORDER_THICKNESS),
			new Collider(-BORDER_THICKNESS, 0, BORDER_THICKNESS, SCREEN_SIZE.y) });
	}

	void refresh() {
		position = 0;
		Entity::entities.push_back(this);
	}

	void update() override {
		Vector2D pp = position;

		for (auto&& p : Player::players) {
			const double walkBorderPlus = 0.75;
			const double walkBorderMinus = 0.25;

			//Left
			if (position.x + SCREEN_SIZE.x * walkBorderMinus > p->position.x + SCALE / 2 * double(PLAYER_TEXTURE.width)) {
				double destX = p->position.x + SCALE / 2 * double(PLAYER_TEXTURE.width) - SCREEN_SIZE.x * walkBorderMinus;
				if (destX >= 0) position.x = destX;

			}

			// Right
			if (position.x + SCREEN_SIZE.x * walkBorderPlus < p->position.x + SCALE / 2 * double(PLAYER_TEXTURE.width)) {
				double destX = p->position.x + SCALE / 2 * double(PLAYER_TEXTURE.width) - SCREEN_SIZE.x * walkBorderPlus;
				if (destX <= double(SCREEN_SIZE.x) * (double(SCREEN_MAP_RATIO) - 1)) position.x = destX;
			}

			// Up
			if (position.y + SCREEN_SIZE.y * walkBorderMinus > p->position.y + SCALE / 2 * double(PLAYER_TEXTURE.height)) {
				double destY = p->position.y + SCALE / 2 * double(PLAYER_TEXTURE.height) - SCREEN_SIZE.y * walkBorderMinus;
				if (destY >= 0) position.y = destY;
			}

			// Down
			if (position.y + SCREEN_SIZE.y * walkBorderPlus < p->position.y + SCALE / 2 * double(PLAYER_TEXTURE.height)) {
				double destY = p->position.y + SCALE / 2 * double(PLAYER_TEXTURE.height) - SCREEN_SIZE.y * walkBorderPlus;
				if (destY <= double(SCREEN_SIZE.y) * (double(SCREEN_MAP_RATIO) - 1)) position.y = destY;
			}
		}

		const Vector2D dif = position - pp;
		for (Collider* c : colliders.colliders) c->position += dif;
	}
};