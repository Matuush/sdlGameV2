#pragma once
#include <vector>
#include <SDL.h>
#include "RenderWindow.h"

class Map {
private:
	int w, h;
public:
	inline void render(int width, int height, SDL_Texture* nothingTexture, SDL_Texture* waterTexture, SDL_Texture* dirtTexture, SDL_Texture* grassTexture, RenderWindow& window);
	std::vector<std::vector<char>> map;
	Map(int width, int height);
	std::vector<std::vector<char>> create();
	std::vector<std::vector<char>> get();

};