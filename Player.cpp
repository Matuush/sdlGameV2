#include <cmath>
#include <iostream>

#include "Player.h"

Player::Player(float p_x, float p_y, SDL_Texture* p_tex){
	x = p_x;
	y = p_y;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
	collider.x = (int)x + 24;
	collider.y = (int)y + 22;
	collider.w = 16 * 4;
	collider.h = 28 * 4;
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

void Player::handleMove() {
	// Straight
	if (left && !right && ((!up && !down) || (up && down))) x -= speed;
	if (right && !left && ((!up && !down) || (up && down))) x += speed;
	if (up && !down && ((!left && !right) || (left && right))) y -= speed;
	if (down && !up && ((!left && !right) || (left && right))) y += speed;
	// Diagonal
	if (up && left && !down && !right) { 
		x -= speed / (float)sqrt(2); 
		y -= speed / (float)sqrt(2);
	}
	if (up && right && !down && !left) {
		x += speed / (float)sqrt(2);
		y -= speed / (float)sqrt(2);
	}
	if (right && down && !left && !up) {
		x += speed / (float)sqrt(2);
		y += speed / (float)sqrt(2);
	}
	if (down && left && !up && !right) {
		x -= speed / (float)sqrt(2);
		y += speed / (float)sqrt(2);
	}
	// Collider moving
	collider.x = (int)x + 24 * 4;
	collider.y = (int)y + 22 * 4;
	// Edges
	if ((collider.x < 0) && (left && !right)) x = -24 * SCALE;
	if ((collider.y < 0) && (up && !down)) y = -22 * SCALE;
	if ((collider.x + collider.w > mapSizeWidth) && right && !left) x = mapSizeWidth - collider.w - 24 * SCALE;
	if ((collider.y + collider.h > mapSizeHeight) && down && !up) y = mapSizeHeight - collider.h - 22 * SCALE;
}