#pragma once
#include "Player.h"

struct Camera : public Entity {
	double x = 0, y = 0, w = SCREEN_SIZE.x, h = SCREEN_SIZE.y;

	Camera() : Entity() {
		init();
		currentFrame = { 0, 0, NOTHING_TEXTURE.width, NOTHING_TEXTURE.height };
		textureID = NOTHING_TEXTURE.id;

		position = SCREEN_SIZE;
		colliders.push_back(RectangleCollider(0, SCREEN_SIZE.y, SCREEN_SIZE.x, BORDER_THICKNESS));
		colliders.push_back(RectangleCollider(SCREEN_SIZE.x, 0, BORDER_THICKNESS, SCREEN_SIZE.y));
		colliders.push_back(RectangleCollider(0, -BORDER_THICKNESS, SCREEN_SIZE.x, BORDER_THICKNESS));
		colliders.push_back(RectangleCollider(-BORDER_THICKNESS, 0, BORDER_THICKNESS, SCREEN_SIZE.y));
	}

	void refresh() {
		x = 0, y = 0;
		Entity::entities.push_back(this);
	}

	void update() override {
		bool left = false, right = false, up = false, down = false;

		Vector2D pp = position;

		for (auto&& p : Player::players) {
			const double walkBorderPlus = 0.75;
			const double walkBorderMinus = 0.25;

			//Left
			if (x + SCREEN_SIZE.x * walkBorderMinus > p->position.x + 2 * double(PLAYER_TEXTURE.width)) {
				double destX = p->position.x + 2 * double(PLAYER_TEXTURE.width) - SCREEN_SIZE.x * walkBorderMinus;
				if (destX >= 0)
					x = destX;

			}

			// Right
			if (x + SCREEN_SIZE.x * walkBorderPlus < p->position.x + 2 * double(PLAYER_TEXTURE.width)) {
				double destX = p->position.x + 2 * double(PLAYER_TEXTURE.width) - SCREEN_SIZE.x * walkBorderPlus;
				if (destX <= double(SCREEN_SIZE.x) * (double(SCREEN_MAP_RATIO) - 1))
					x = destX;
			}

			// Up
			if (y + SCREEN_SIZE.y * walkBorderMinus > p->position.y + 2 * double(PLAYER_TEXTURE.height)) {
				double destY = p->position.y + 2 * double(PLAYER_TEXTURE.height) - SCREEN_SIZE.y * walkBorderMinus;
				if (destY >= 0)
					y = destY;
			}

			// Down
			if (y + SCREEN_SIZE.y * walkBorderPlus < p->position.y + 2 * double(PLAYER_TEXTURE.height)) {
				double destY = p->position.y + 2 * double(PLAYER_TEXTURE.height) - SCREEN_SIZE.y * walkBorderPlus;
				if (destY <= double(SCREEN_SIZE.y) * (double(SCREEN_MAP_RATIO) - 1))
					y = destY;
			}
		}

		position.x = x + w;
		position.y = y + h;

		Vector2D dif = position - pp;
		for (RectangleCollider& c : colliders) {
			c.x += dif.x;
			c.y += dif.y;
		}
	}
};