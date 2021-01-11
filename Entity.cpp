#include "Entity.h"

Entity::Entity(float p_x, float p_y, char p_id) : x(p_x), y(p_y), textureID(p_id) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	collider.x = (int)x;
	collider.y = (int)y;
	collider.w = currentFrame.w;
	collider.h = currentFrame.h;
}

Entity::Entity() : x(100), y(100), textureID(0) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	collider.x = (int)x;
	collider.y = (int)y;
	collider.w = currentFrame.w;
	collider.h = currentFrame.h;
}

void Entity::changeTextureID(char p_id) { textureID = p_id; }

float Entity::getX() { return x; }

float Entity::getY() { return y; }

void Entity::setPos(float p_x, float p_y) {
	x = p_x;
	y = p_y;
}

char Entity::getTextureID() { return textureID; }

SDL_Rect* Entity::getCurrentFrame() { return &currentFrame; }
