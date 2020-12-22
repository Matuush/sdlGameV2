#include "Tile.h"
#include <string>

Tile::Tile(int p_x, int p_y, const char* texChar, RenderWindow* p_window) : window(p_window) {
	texture = texChar;
	this->x = (float)(p_x);
	this->y = (float)(p_y);
	tex = window->loadTexture(texChar);
	currentFrame.w = tileSize / SCALE;
	currentFrame.h = tileSize / SCALE;
	currentFrame.x = currentFrame.y = 0;
	collider.w = tileSize;
	collider.h = tileSize;
	collider.x = (int)x;
	collider.y = (int)y;
}

void Tile::changeTexture(const char* texChar) {
	texture = texChar;
	tex = window->loadTexture(texChar);
}