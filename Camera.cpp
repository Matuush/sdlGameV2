#include "Camera.h"

Camera::Camera() : Entity() {
	init();
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = nothingTexture.width;
	currentFrame.h = nothingTexture.height;

	textureID = nothingTexture.id;

	position.x = screenWidth, position.y = screenHeight;
	colliders.push_back(RectangleCollider(0, screenHeight, screenWidth, 100));
	colliders.push_back(RectangleCollider(screenWidth, 0, 100, screenHeight));
	colliders.push_back(RectangleCollider(0, -100, screenWidth, 100));
	colliders.push_back(RectangleCollider(-100, 0, 100, screenHeight));
	solid = true;
}

void Camera::update() {
	bool left = 0, right = 0, up = 0, down = 0;
	for (auto&& p : Player::players) {
		const double walkBorderPlus = 0.75;
		const double walkBorderMinus = 0.25;

		//Left
		if (x + screenWidth * walkBorderMinus > p->position.x + 2 * double(playerTexture.width)) {
			double destX = p->position.x + 2 * double(playerTexture.width) - screenWidth * walkBorderMinus;
			if (destX >= 0) {
				left = true;
				if (!right)
					x = destX;
			}
		}
		else if (left)left = false;

		// Right
		if (x + screenWidth * walkBorderPlus < p->position.x + 2 * double(playerTexture.width)) {
			double destX = p->position.x + 2 * double(playerTexture.width) - screenWidth * walkBorderPlus;
			if (destX <= double(screenWidth) * (double(screenMapRatio) - 1)) {
				right = true;
				if (!left)
					x = destX;
			}
		}
		else if (right)right = false;
		
		// Up
		if (y + screenHeight * walkBorderMinus > p->position.y + playerTexture.height / 2) {
			double destY = p->position.y + 2 * double(playerTexture.height) - screenHeight * walkBorderMinus;
			if (destY >= 0) {
				up = true;
				if (!down)
					y = destY;
			}
		}
		else if (up)up = false;

		// Down
		if (y + screenHeight * walkBorderPlus < p->position.y + playerTexture.height / 2) {
			double destY = p->position.y + 2 * double(playerTexture.height) - screenHeight * walkBorderPlus;
			if (destY <= double(screenHeight) * (double(screenMapRatio) - 1)) {
				down = true;
				if (!up)
					y = destY;
			}
		}
		else if (down)down = false;
	}
}