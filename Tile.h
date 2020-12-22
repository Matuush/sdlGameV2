#pragma once
#include "Constants.h"
#include "Entity.h"
#include "RenderWindow.h"

class Tile : public Entity{
	RenderWindow* window;
public:
	const char* texture;
	Tile() = default;
	Tile(int p_x, int p_y, const char* texChar, RenderWindow* p_windoow);
	void changeTexture(const char* texChar);
};