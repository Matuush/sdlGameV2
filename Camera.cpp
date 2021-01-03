#include "Camera.h"

Camera::Camera(){
	camera.x = 0;
	camera.y = 0;
	camera.w = screenWidth;
	camera.h = screenHeight;
}

void Camera::move(Player* player) {
	const float walkBorderRight = (float)0.875;
	const float walkBorderDown = (float)0.75;
	const float walkBorderLeft = (float)0.045;
	const float walkBorderUp = (float)0.2;

	if ((float)(x + screenWidth * walkBorderRight) < player->getX() + player->collider.w) {
		if ((player->getX() + (float)(player->collider.w - screenWidth * walkBorderRight)) <= screenWidth * (screenMapRatio - 1)) {
			x = (float)(player->getX() + player->collider.w - screenWidth * walkBorderRight);
		}
	}
	if ((float)(y + screenHeight * walkBorderDown) < player->getY() + player->collider.h) {
		if ((player->getY() + (float)(player->collider.h - screenHeight * walkBorderDown)) <= screenHeight * (screenMapRatio - 1)) {
			y = (float)(player->getY() + player->collider.h - screenHeight * walkBorderDown);
		}
	}
	if ((float)(x + screenWidth * walkBorderLeft) > player->getX() + player->collider.w) {
		if ((player->getX() + (float)(player->collider.w - screenWidth * walkBorderLeft)) >= 0) {
			x = (float)(player->getX() + player->collider.w - screenWidth * walkBorderLeft);
		}
	}
	if ((float)(y + screenHeight * walkBorderUp) > player->getY() + player->collider.h) {
		if ((player->getY() + (float)(player->collider.h - screenHeight * walkBorderUp)) >= 0) {
			y = (float)(player->getY() + player->collider.h - screenHeight * walkBorderUp);
		}
	}

	camera.x = (int)x;
	camera.y = (int)y;
}