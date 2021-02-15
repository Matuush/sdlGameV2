#include "Map.h"

Map::Map() {
	for (int i = 0; i < mapTileCountWidth; i++) {
		std::vector<Entity*> line;
		tileMap.push_back(line);
		for (int j = 0; j < mapTileCountHeight; j++) 
			tileMap[i].push_back(new Entity(Vector2D(i * tileSize, j * tileSize), nothingTexture));
	}
	generateMap();
}

inline void Map::generateMap() {
	for (int width = 0; width < mapTileCountWidth; width++)
		for (int height = 0; height < mapTileCountHeight; height++) 
			tileMap[width][height]->textureID = dirtTexture.id;

	// Manually changed tiles
	tileMap[5][5]->textureID = waterTexture.id;
	tileMap[5][5]->solid = true;
	tileMap[4][4]->textureID = waterTexture.id;
	tileMap[4][4]->solid = true;
	tileMap[9][9]->textureID = grassTexture.id;
	tileMap[9][10]->textureID = grassTexture.id;
	tileMap[10][9]->textureID = grassTexture.id;
	tileMap[10][10]->textureID = grassTexture.id;
	/*
	const int waterVolume = (mapTileCountWidth * mapTileCountHeight) / 10; // How much water
	
	// Handling seed
	int unicodeSum = 0;
	for (char i : seed) unicodeSum += i;
	srand(unicodeSum);

	// Decide Lake / River / 2 Rivers
	switch (unicodeSum % 3) {
	case 0: // Lake
		break;

	case 1: // River
		break;

	case 2: // 2 Rivers
		break;
	}*/
}

Map::~Map() {
	for (auto&& i : tileMap)
		for (auto&& j : i)
			delete j;
}