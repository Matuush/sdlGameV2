#pragma once
#include "Player.hpp"

struct Camera {
	double w = SCREEN_SIZE.x, h = SCREEN_SIZE.y;
	Vector2D position;
	Camera() = default;

	void refresh() {
		position = 0;
	}

	void move() {
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
	}
};