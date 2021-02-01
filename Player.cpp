#include "Player.h"

std::vector<Player*> Player::players;

Player::Player(Vector2D p_position, std::vector<std::vector<Entity*>>* p_map) : Entity() {
	position = p_position;
	lastPos = position;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = playerTexture.width;
	currentFrame.h = playerTexture.height;

	colliders.push_back(RectangleCollider(position.x + (double)playerHitboxDistanceX * SCALE,
		position.y + (double)playerHitboxDistanceY * SCALE,
		(double)playerHitboxWidth * SCALE,
		(double)playerHitboxHeight * SCALE));

	map = p_map;

	textureID = playerTexture.id;

	Player::players.push_back(this);
	Entity::entities.push_back(this);
}

void Player::changeSprite() {
	if (((left == 0 && right == 0) || (left == 1 && right == 1)) && ((up == 0 && down == 0) || (up == 1 && down == 1))) {
		currentFrame.y = rawPlayer;
		currentFrame.x = (SDL_GetTicks() / 100 % 4 + 1) * rawPlayer;
	}
	else {
		int tick = (int)(SDL_GetTicks() / (500 / SPEED)) % 6;
		if (tick != 5) {
			currentFrame.y = 0;
			currentFrame.x = tick * rawPlayer;
		}
		else {
			currentFrame.y = rawPlayer;
			currentFrame.x = 0;
		}
	}
}

void Player::move(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_w:
			up = 1;
			break;
		case SDLK_a:
			left = 1;
			lastRight = 0;
			break;
		case SDLK_s:
			down = 1;
			break;
		case SDLK_d:
			right = 1;
			lastRight = 1;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym) {
		case SDLK_w:
			up = 0;
			break;
		case SDLK_a:
			left = 0;
			if (right && !lastRight) lastRight = 1;
			break;
		case SDLK_s:
			down = 0;
			break;
		case SDLK_d:
			right = 0;
			if (left && lastRight) lastRight = 0;
			break;
		}
		break;
	}
}

unsigned int ceiling(double num) {
	double f = floor(num);
	if (num == f) return static_cast<unsigned int>(f);
	return static_cast<unsigned int>(f + 1);
}

void Player::handleMove() {
/*	lastPos = position;

	// Straight
	if (left && !right && ((!up && !down) || (up && down))) x -= SPEED;
	if (right && !left && ((!up && !down) || (up && down))) x += SPEED;
	if (up && !down && ((!left && !right) || (left && right))) y -= SPEED;
	if (down && !up && ((!left && !right) || (left && right))) y += SPEED;

	const int TWO = 2;
	// Diagonal
	if (up && left && !down && !right) { 
		x -= SPEED / (float)sqrt(TWO);
		y -= SPEED / (float)sqrt(TWO);
	}
	if (up && right && !down && !left) {
		x += SPEED / (float)sqrt(TWO);
		y -= SPEED / (float)sqrt(TWO);
	}
	if (right && down && !left && !up) {
		x += SPEED / (float)sqrt(TWO);
		y += SPEED / (float)sqrt(TWO);
	}
	if (down && left && !up && !right) {
		x -= SPEED / (float)sqrt(TWO);
		y += SPEED / (float)sqrt(TWO);
	}

	// Collider moving
	moveCollider();

	// AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH DNT
		double t_x = (double)((double)collider.x / (double)tileSize);
		double t_y = (double)((double)collider.y / (double)tileSize);
		bool temX = (collider.x % tileSize + collider.w) >= tileSize;
		bool temY = (collider.y % tileSize + collider.h) >= tileSize;
		bool r_x = 0, r_y = 0;
		if ((floor(t_x) <= (double)(mapTileCountWidth - 1)) && (floor(t_x) >= 0) && (ceiling(t_x) <= mapTileCountWidth - 1) && (ceiling(t_x) >= 0) && 
			(floor(t_y) <= (double)(mapTileCountHeight - 1)) && (floor(t_y) >= 0) && (ceiling(t_y) <= mapTileCountHeight - 1) && (ceiling(t_y) >= 0)) {
		if ((map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>(floor(t_y))].getTextureID() == waterTexture.id) ||
			(temX && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>(floor(t_y))].getTextureID() == waterTexture.id) ||
			(temY && map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id) ||
			(temX && temY && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id)) {
			t_x = (double)((double)((double)lastPos[0] + (double)playerHitboxDistanceY * (double)SCALE) / (double)tileSize);
			if ((map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>(floor(t_y))].getTextureID() == waterTexture.id) ||
				(temX && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>(floor(t_y))].getTextureID() == waterTexture.id) ||
				(temY && map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id) ||
				(temX && temY && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id)) r_y = 1;
			t_x = (double)((double)collider.x / (double)tileSize);
			t_y = (double)((double)((double)lastPos[1] + (double)playerHitboxDistanceX * (double)SCALE) / (double)tileSize);
			if ((map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>(floor(t_y))].id == waterTexture.id) ||
				(temX && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>(floor(t_y))].getTextureID() == waterTexture.id) ||
				(temY && map->at(static_cast<unsigned int>(floor(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id) ||
				(temX && temY && map->at(static_cast<unsigned int>((double)ceiling(t_x)))[static_cast<unsigned int>((double)ceiling(t_y))].getTextureID() == waterTexture.id)) r_x = 1;
			return revertMove(r_x, r_y);
		}
	}
	
	// Edges
	if ((collider.x < 0 && left && !right) || ((collider.x + collider.w > screen->x + screen->w) && right && !left)) revertMove(1, 0);
	if ((collider.y < 0 && up && !down) || ((collider.y + collider.h > screen->y + screen->h) && down && !up)) revertMove(0, 1);
	*/
}

void Player::stopMomentum() {
	up = 0;
	down = 0;
	left = 0;
	right = 0;
}

inline void Player::revertMove(bool h_x, bool h_y) { position = lastPos; }