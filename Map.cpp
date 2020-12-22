#include "Map.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "Entity.h"

Map::Map(RenderWindow* p_window) : window(p_window){
	for (int i = 0; i < mapTileCountWidth; i++) {
		std::vector<Tile> line;
		tileMap.push_back(line);
		for (int j = 0; j < mapTileCountHeight; j++) {
			Tile tile((i * tileSize), (j * tileSize), nothingTexture, window);
			tileMap[i].push_back(tile);
		}
	}
}

void Map::generateMap(std::string seed) {
	for (int width = 0; width < mapTileCountWidth; width++) {
		for (int height = 0; height < mapTileCountHeight; height++) this->tileMap[width][height].changeTexture(dirtTexture);
	}

	const int waterVolume = (mapTileCountWidth * mapTileCountHeight)/10;

	int unicodeSum = 0;
	for (char i : seed) unicodeSum += i;
	srand(unicodeSum);
	const int startX = rand()% mapTileCountWidth;
	const int startY = rand()% mapTileCountHeight;
	int currentX = startX; // 2
	int currentY = startY; // 6

	switch (unicodeSum % 3) {
	case 0: // Rybnik
	{
		tileMap[currentX][currentY].changeTexture(waterTexture);
		if(currentY != mapTileCountHeight - 1) currentY++;
		for (int i = 1; i < waterVolume; i++) {
			tileMap[currentX][currentY].changeTexture(waterTexture);
			int currentXplus = currentX + 1;
			int currentXminus = currentX - 1;
			int currentYplus = currentY + 1;
			int currentYminus = currentY - 1;
			if (currentYplus == mapTileCountHeight) {
				int randomDirtY = 0;
				while (tileMap[currentX][randomDirtY].texture != dirtTexture) randomDirtY++;
				currentYplus = randomDirtY;
			}
			if (currentYminus == -1) {
				int randomDirtY = 0;
				while (tileMap[currentX][randomDirtY].texture != dirtTexture) randomDirtY++;
				currentYminus = randomDirtY;
			}
			if (currentXplus == mapTileCountWidth) {
				int randomDirtX = 0;
				while (tileMap[randomDirtX][currentY].texture != dirtTexture) randomDirtX++;
				currentXplus = randomDirtX;
			}
			if (currentXminus == -1) {
				int randomDirtX = 0;
				while (tileMap[randomDirtX][currentY].texture != dirtTexture) randomDirtX++;
				currentXminus = randomDirtX;
			}
			if ((tileMap[currentX][currentYminus].texture == waterTexture) && (tileMap[currentXplus][currentY].texture == dirtTexture) && (currentX != mapSizeWidth - 1)) currentX++;
			else if ((tileMap[currentXminus][currentY].texture == waterTexture) && (tileMap[currentX][currentYminus].texture == dirtTexture) && (currentY != 0)) currentY--;
			else if ((tileMap[currentX][currentYplus].texture == waterTexture) && (tileMap[currentXminus][currentY].texture == dirtTexture) && (currentX != 0)) currentX--;
			else if ((tileMap[currentXplus][currentY].texture == waterTexture) && (tileMap[currentX][currentYplus].texture == dirtTexture) && (currentY != mapSizeHeight - 1)) currentY++;
			else i = waterVolume;

			// Ukousni kus v rohu a placni ho jinam
		}
	}
	break;

	case 1: // Reka
		break;

	case 2: // 2 Reky
		break;
	}
}