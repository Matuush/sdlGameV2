#pragma once
#include <vector>
#include <cmath>

#include <SDL.h>

#include "Vector2D.h"
#include "Entity.h"
#include "RenderWindow.h"

#include "Constants.h"

struct Map {
	RenderWindow* window = NULL;
	std::vector<std::vector<Entity>> tileMap;

	Map() = default;
	Map(RenderWindow* window);

	inline void generateMap();

};