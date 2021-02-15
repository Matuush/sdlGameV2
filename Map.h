#pragma once
#include <vector>
#include <cmath>

#include <SDL.h>

#include "Vector2D.h"
#include "Entity.h"

#include "Constants.h"

struct Map {
	std::vector<std::vector<Entity*>> tileMap;

	Map();
	~Map();

	inline void generateMap();

};