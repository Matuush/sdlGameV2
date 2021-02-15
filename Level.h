#pragma once
#include "SDL.h"
#include <vector>

#include "Entity.h"
#include "Map.h"
#include "Player.h"

#include"Constants.h"

struct Level {
	Map map = Map();
	Entity borderWall = Entity(Vector2D(mapSizeWidth, mapSizeHeight));
	Player player1 = Player(Vector2D(10, 10), &map.tileMap);
	Player player2 = Player(Vector2D(10, 200), &map.tileMap);

	Level();
	~Level();
};