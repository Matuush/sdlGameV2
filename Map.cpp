#include "Map.h"

Map::Map(RenderWindow* window) : window(window){
	for (int i = 0; i < mapTileCountWidth; i++) {
		std::vector<Entity> line;
		tileMap.push_back(line);
		for (int j = 0; j < mapTileCountHeight; j++) {
			Entity tile((float)(i * tileSize), (float)(j * tileSize), NOTHING);
			tileMap[i].push_back(tile);
		}
	}

	generateMap();
}

inline void Map::generateMap() {
	for (int width = 0; width < mapTileCountWidth; width++) {
		for (int height = 0; height < mapTileCountHeight; height++) tileMap[width][height].changeTextureID(DIRT);
	}

	const int waterVolume = (mapTileCountWidth * mapTileCountHeight)/10;

	int unicodeSum = 0;
	for (char i : seed) unicodeSum += i;

	srand(unicodeSum);
	const int startX = rand()% mapTileCountWidth;
	const int startY = rand()% mapTileCountHeight;
	int currentX = startX;
	int currentY = startY;

	switch (unicodeSum % 3) {
	case 0: // Rybnik
	break;

	case 1: // Reka
		break;

	case 2: // 2 Reky
		break;
	}
}