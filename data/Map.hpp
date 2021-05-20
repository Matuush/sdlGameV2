#pragma once
#include "../Entity.hpp"

class Map {
public:
	Entity* tileMap[SCREEN_TILE_COUNT_Y * SCREEN_MAP_RATIO * SCREEN_RATIO][SCREEN_TILE_COUNT_Y * SCREEN_MAP_RATIO];
	Entity* borderWall = new Entity(MAP_SIZE);

	Map() {
		for (int i = 0; i < MAP_TILE_COUNT.x; i++)
			for (int j = 0; j < MAP_TILE_COUNT.y; j++)
				tileMap[i][j] = new Entity(Vector2D(i * TILE_SIZE, j * TILE_SIZE), NOTHING_TEXTURE);

		generateMap();
		manuallyChangeTiles();

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
		for (int width = 0; width < MAP_TILE_COUNT.x; width++)
			for (int height = 0; height < MAP_TILE_COUNT.y; height++)
				changeTile(width, height, DIRT_TEXTURE);
	}
	inline void manuallyChangeTiles() {
		changeTile(4, 4, WATER_TEXTURE, true);
		changeTile(5, 5, WATER_TEXTURE, true);
		changeTile(9, 9, GRASS_TEXTURE);
		changeTile(9, 10, GRASS_TEXTURE);
		changeTile(10, 9, GRASS_TEXTURE);
		changeTile(10, 10, GRASS_TEXTURE);
	}
	inline void changeTile(int x, int y, Texture p_texture) { tileMap[x][y]->textureID = p_texture.id; }
	inline void changeTile(int x, int y, Texture p_texture, bool solid) {
		tileMap[x][y]->textureID = p_texture.id;
		tileMap[x][y]->solid = solid;
	}
};