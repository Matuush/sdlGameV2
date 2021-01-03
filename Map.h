#pragma once
#include <vector>
#include <cmath>

#include <SDL.h>

#include "Entity.h"
#include "RenderWindow.h"

#include "Constants.h"

class Map {
public:
	RenderWindow* window;
	std::vector<std::vector<Entity>> tileMap;

	Map() = default;
	Map(RenderWindow* window);

	inline void generateMap();

};