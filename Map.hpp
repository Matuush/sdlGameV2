#pragma once
#include <fstream>
#include <array>
#include "Entity.hpp"

//! hepl!
//? hepl?
//TODO hepl
// hepl.
class Map {
public:
	std::array<std::array<Entity*, SCREEN_TILE_COUNT_Y * SCREEN_MAP_RATIO>, SCREEN_TILE_COUNT_Y * SCREEN_MAP_RATIO * SCREEN_RATIO> tileMap;
	Entity* borderWall = new Entity(MAP_SIZE);

	Map() {
		for (int i = 0; i < MAP_TILE_COUNT.x; i++)
			for (int j = 0; j < MAP_TILE_COUNT.y; j++)
				tileMap[i][j] = new Entity(Vector2D(i * TILE_SIZE, j * TILE_SIZE), DIRT_TEXTURE);

		generateMap();

		borderWall->solid = true, borderWall->display = false;
		borderWall->colliders = MultiCollider({
			new Collider(-BORDER_THICKNESS, MAP_SIZE.y, MAP_SIZE.x + 2 * BORDER_THICKNESS, BORDER_THICKNESS),
			new Collider(MAP_SIZE.x, 0, BORDER_THICKNESS, MAP_SIZE.y),
			new Collider(-BORDER_THICKNESS, -BORDER_THICKNESS, MAP_SIZE.x + 2 * BORDER_THICKNESS, BORDER_THICKNESS),
			new Collider(-BORDER_THICKNESS, 0, BORDER_THICKNESS, MAP_SIZE.y)
		});
	}
	~Map() {
		for (auto&& i : tileMap)
			for (Entity* j : i)
				delete j;
		delete borderWall;
	}

private:
	inline void generateMap() {
		changeTile(4, 4, true);
		changeTile(5, 5, true);
	}
	inline void changeTile(int x, int y, bool solid) {
		tileMap[x][y]->solid = solid;
	}
};