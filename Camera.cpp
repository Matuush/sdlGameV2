#include "Camera.h"

Camera::Camera(){
}

void Camera::move(Player* player) {
	const double walkBorderPlus = 0.75;
	const double walkBorderMinus = 0.25;

	// Right
	if (x + screenWidth * walkBorderPlus < player->position.x)
		if (player->position.x - screenWidth * walkBorderPlus <= (double)(screenWidth * (screenMapRatio - 1)))
			x = player->position.x - screenWidth * walkBorderPlus;

	// Down
	if (y + screenHeight * walkBorderPlus < player->position.y + 1.5 * player->colliders[0].h)
		if ((player->position.y + 1.5 * player->colliders[0].h - screenHeight * walkBorderPlus) <= (double)(screenHeight * (screenMapRatio - 1)))
			y = player->position.y + 1.5 * player->colliders[0].h - screenHeight * walkBorderPlus;

	//Left
	if (x + screenWidth * walkBorderMinus > player->position.x + 4 * player->colliders[0].w)
		if (player->position.x + 4 * player->colliders[0].w - screenWidth * walkBorderMinus >= 0)
			x = player->position.x + 4 * player->colliders[0].w - screenWidth * walkBorderMinus;

	// Up
	if (y + screenHeight * walkBorderMinus > player->position.y + player->colliders[0].h)
		if (player->position.y + player->colliders[0].h - screenHeight * walkBorderMinus >= 0)
			y = player->position.y + player->colliders[0].h - screenHeight * walkBorderMinus;
}