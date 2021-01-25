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
	for (int width = 0; width < mapTileCountWidth; width++)
		for (int height = 0; height < mapTileCountHeight; height++) 
			tileMap[width][height].changeTextureID(DIRT);

	// Manually changed tiles
	tileMap[5][5].changeTextureID(WATER);
	tileMap[4][4].changeTextureID(WATER);
	tileMap[9][9].changeTextureID(GRASS);
	tileMap[9][10].changeTextureID(GRASS);
	tileMap[10][9].changeTextureID(GRASS);
	tileMap[10][10].changeTextureID(GRASS);

	const int waterVolume = (mapTileCountWidth * mapTileCountHeight) / 10; // How much water

	// Handling seed
	int unicodeSum = 0;
	for (char i : seed) unicodeSum += i;
	srand(unicodeSum);

	//Starting position of generation
	const int startX = rand()% mapTileCountWidth;
	const int startY = rand()% mapTileCountHeight;
	int currentX = startX;
	int currentY = startY;

	// Decide Lake / River / 2 Rivers
	switch (unicodeSum % 3) {
	case 0: // Lake
		break;

	case 1: // River
		break;

	case 2: // 2 Rivers
		break;
	}
}