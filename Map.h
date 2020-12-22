#pragma once
#include <vector>
#include <SDL.h>

#include "RenderWindow.h"
#include "Camera.h"
#include "Tile.h"
#include "Constants.h"

class Map {
private:
	RenderWindow* window;
public:
	std::vector<std::vector<Tile>> tileMap;

	Map(RenderWindow* p_window);

	void generateMap(std::string seed);

};