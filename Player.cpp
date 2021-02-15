#include "Player.h"

std::vector<Player*> Player::players;

Player::Player(Vector2D p_position, std::vector<std::vector<Entity*>>* p_map) : Entity() {
	position = p_position;
	lastPos = position;
	terminalVelocity = playerTerminalVelocity;

	solid = 1;

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = playerTexture.width;
	currentFrame.h = playerTexture.height;

	colliders.push_back(RectangleCollider(position.x + (double)playerHitboxDistanceX * SCALE,
		position.y + (double)playerHitboxDistanceY * SCALE,
		(double)playerHitboxWidth * SCALE,
		(double)playerHitboxHeight * SCALE));

	keyState;

	map = p_map;

	textureID = playerTexture.id;

	Player::players.push_back(this);
	Entity::entities.push_back(this);
}

void Player::update() {
	velocity = (velocity + acceleration);
	if (keyState.w != prevKeyState.w) {
		if (keyState.w) velocity.y -= SPEED;
		else velocity.y += SPEED;
	}
	if (keyState.a != prevKeyState.a) {
		if (keyState.a) velocity.x -= SPEED;
		else velocity.x += SPEED;
	}
	if (keyState.s != prevKeyState.s) {
		if (keyState.s) velocity.y += SPEED;
		else velocity.y -= SPEED;
	}
	if (keyState.d != prevKeyState.d) {
		if (keyState.d) velocity.x += SPEED;
		else velocity.x -= SPEED;
	}

	velocity.limit(terminalVelocity);

	updatePosition();
	prevKeyState = keyState;

	changeSprite();
}

void Player::input(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_w:
			keyState.w = 1;
			break;
		case SDLK_a:
			keyState.a = 1;
			lastRight = 0;
			break;
		case SDLK_s:
			keyState.s = 1;
			break;
		case SDLK_d:
			keyState.d = 1;
			lastRight = 1;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym) {
		case SDLK_w:
			keyState.w = 0;
			break;
		case SDLK_a:
			keyState.a = 0;
			if (keyState.d && !lastRight) lastRight = 1;
			break;
		case SDLK_s:
			keyState.s = 0;
			break;
		case SDLK_d:
			keyState.d = 0;
			if (keyState.a && lastRight) lastRight = 0;
			break;
		}
		break;
	}
}

void Player::changeSprite() {
	if (((keyState.a == 0 && keyState.d == 0) || (keyState.a == 1 && keyState.d == 1)) && ((keyState.w == 0 && keyState.s == 0) || (keyState.w == 1 && keyState.s == 1))) {
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