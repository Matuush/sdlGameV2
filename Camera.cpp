#include "Camera.h"

Camera::Camera(){
	camera.x = camera.y = 0;
	camera.w = screenWidth;
	camera.h = screenHeight;
}

void Camera::move(Player* player) {
	const float walkBorderPlus = (float)0.75;
	const float walkBorderMinus = (float)0.25;

	// Right
	if ((float)(x + screenWidth * walkBorderPlus) < player->getX())
		if ((player->getX() - (float)(screenWidth * walkBorderPlus)) <= screenWidth * (screenMapRatio - 1)) 
			x = (float)(player->getX() - screenWidth * walkBorderPlus);

	// Down
	if ((float)(y + screenHeight * walkBorderPlus) < player->getY() + (float)(1.5 * player->collider.h))
		if ((player->getY() + (float)((float)(1.5 * player->collider.h) - screenHeight * walkBorderPlus)) <= screenHeight * (screenMapRatio - 1))
			y = (float)(player->getY() + (float)(1.5 * player->collider.h) - screenHeight * walkBorderPlus);

	//Left
	if ((float)(x + screenWidth * walkBorderMinus) > player->getX() + 4 * player->collider.w)
		if ((player->getX() + (float)(4 * player->collider.w - screenWidth * walkBorderMinus)) >= 0)
			x = (float)(player->getX() + 4 * player->collider.w - screenWidth * walkBorderMinus);

	// Up
	if ((float)(y + screenHeight * walkBorderMinus) > player->getY() + player->collider.h)
		if ((player->getY() + (float)(player->collider.h - screenHeight * walkBorderMinus)) >= 0)
			y = (float)(player->getY() + player->collider.h - screenHeight * walkBorderMinus);

	camera.x = (int)x;
	camera.y = (int)y;
}