#include "Map.h"
#include <iostream>
#include <cmath>
#include "Entity.h"

Map::Map(int width, int height) : w(width), h(height) {
	for (int i = 0; i < w; i++) {
		std::vector<char> line;
		map.push_back(line);
		for (int j = 0; j < h; j++) map[i].push_back(0);
	}
}

void Map::setWindow(RenderWindow* p_window) {
	window = p_window;
}

void Map::setTextures() {
	nothingTexture = window->loadTexture("textures/nothing.png");
	waterTexture = window->loadTexture("textures/water.png");
	dirtTexture = window->loadTexture("textures/dirt.png");
	grassTexture = window->loadTexture("textures/grass.png");
}

void Map::generateMap(std::string seed) {
	for (int width = 0; width < this->map.size(); width++) {
		for (int height = 0; height < this->map[width].size(); height++) this->map[width][height] = 2;
	}

	const int waterVolume = (w*h)/5;

	int unicodeSum = 0;
	for (int i = 0; i < seed.length(); i++) unicodeSum += seed[i];

	switch (unicodeSum % 3) {
	case 0: // Rybnik
	{
		const int startX = 9;
		const int startY = 4;
		int currentX = startX;
		int currentY = startY;

		map[currentX][currentY] = 1;
		currentY++;
		for (int i = 1; i < 10; i++) {
			map[currentX][currentY] = 1;
			int currentYminus = currentY - 1;
			int currentYplus = currentY + 1;
			int currentXminus = currentX - 1;
			int currentXplus = currentX + 1;
				 if ((map[currentX][currentYminus] == 1) && (map[currentXplus][currentY] == 2)) currentX++;
			else if ((map[currentXminus][currentY] == 1) && (map[currentX][currentYminus] == 2)) currentY--;
			else if ((map[currentX][currentYplus] == 1) && (map[currentXminus][currentY] == 2)) currentX--;
			else if ((map[currentXminus][currentY] == 1) && (map[currentX][currentYplus] == 2)) currentY++;

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

void Map::renderTile(int width, int height) {
	switch (this->map[width][height]) {
	case 0: {
		Entity nothing((float)width * 32, (float)height * 32, nothingTexture);
		window->render(nothing);
		break;
	}
	case 1: {
		Entity water((float)width * 32, (float)height * 32, waterTexture);
		window->render(water);
		break;
	}
	case 2: {
		Entity dirt((float)width * 32, (float)height * 32, dirtTexture);
		window->render(dirt);
		break;
	}
	case 3: {
		Entity grass((float)width * 32, (float)height * 32, grassTexture);
		window->render(grass);
		break;
	}
	default:
		std::cout << "Unknown map tile symbol" << std::endl;
		break;
	}
}