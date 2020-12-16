#pragma once
#include <vector>
#include <SDL.h>
#include <string>
#include "RenderWindow.h"

class Map {
private:
	RenderWindow* window;
	int w, h;
	SDL_Texture* nothingTexture;
	SDL_Texture* waterTexture;
	SDL_Texture* dirtTexture;
	SDL_Texture* grassTexture;
public:
	std::vector<std::vector<char>> map;

	Map(int width, int height);

	void setWindow(RenderWindow* window);
	void setTextures();
	void generateMap(std::string seed);
	void renderTile(int width, int height);

};