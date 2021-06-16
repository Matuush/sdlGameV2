#pragma once
#include "../Player.hpp"

struct Camera {
	double w = SCREEN_SIZE.x, h = SCREEN_SIZE.y;
	Vector2D position;
	Camera() = default;

	void refresh() {
		position = 0;
	}

	void move() {
		const double walkBorderPlus = 0.5;
		const double walkBorderMinus = 0.25;
		const Vector2D walkBorderPos(SCREEN_SIZE.x * walkBorderMinus, SCREEN_SIZE.y * walkBorderMinus);
		const Vector2D walkBorderSize (SCREEN_SIZE.x * walkBorderPlus, SCREEN_SIZE.y * walkBorderPlus);

		for (auto&& p : Player::players) {
			const Vector2D truePos = Vector2D(p->position.x + p->texture.width * SCALE / 2, p->position.y + p->texture.height * SCALE / 2) - position;

			//Left
			if (truePos.x < walkBorderPos.x) {
				double destX = truePos.x + position.x - walkBorderPos.x;
				if (destX >= 0) position.x = destX;
			}
			
			//Right
			else if (truePos.x > walkBorderPos.x + walkBorderSize.x) {
				double destX = truePos.x + position.x - (walkBorderPos.x + walkBorderSize.x);
				if (destX <= MAP_SIZE.x - SCREEN_SIZE.x) position.x = destX;
			}

			//Up
			if (truePos.y < walkBorderPos.y) {
				double destY = truePos.y + position.y - walkBorderPos.y;
				if (destY >= 0) position.y = destY;
			}

			//Down
			else if (truePos.y > walkBorderPos.y + walkBorderSize.y) {
				double destY = truePos.y + position.y - (walkBorderPos.y + walkBorderSize.y);
				if (destY <= MAP_SIZE.y - SCREEN_SIZE.y) position.y = destY;
			}
		}
	}
};