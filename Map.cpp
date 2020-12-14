#include "Map.h"
#include <iostream>
#include "Entity.h"

Map::Map(int width, int height) : w(width), h(height) {
	for (int i = 0; i < w; i++) {
		std::vector<char> line;
		map.push_back(line);
		for (int j = 0; j < h; j++) map[i].push_back(0);
	}
}

std::vector<std::vector<char>> Map::create() {
	return map;
}

inline void Map::render(int width, int height, SDL_Texture* nothingTexture, SDL_Texture* waterTexture, SDL_Texture* dirtTexture, SDL_Texture* grassTexture, RenderWindow& window) {
	switch (this->map[width][height]) {
	case 0: {
		Entity nothing((float)width * 32, (float)height * 32, nothingTexture);
		window.render(nothing);
		break;
	}
	case 1: {
		Entity water((float)width * 32, (float)height * 32, waterTexture);
		window.render(water);
		break;
	}
	case 2: {
		Entity dirt((float)width * 32, (float)height * 32, dirtTexture);
		window.render(dirt);
		break;
	}
	case 3: {
		Entity grass((float)width * 32, (float)height * 32, grassTexture);
		window.render(grass);
		break;
	}
	default:
		std::cout << "Unknown map tile symbol" << std::endl;
		break;
	}
}