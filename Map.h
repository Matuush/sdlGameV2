#pragma once
#include <vector>
#include <SDL.h>
#include "RenderWindow.h"

class Map {
private:
	RenderWindow* window;
	int w, h;
	SDL_Texture* nothingTexture = window->loadTexture("textures/nothing.png");
	SDL_Texture* waterTexture = window->loadTexture("textures/water.png");
	SDL_Texture* dirtTexture = window->loadTexture("textures/dirt.png");
	SDL_Texture* grassTexture = window->loadTexture("textures/grass.png");
public:
	void setTexture(const char* n, const char* w, const char* d, const char* g);
	void render(int width, int height);
	std::vector<std::vector<char>> map;
	Map(int width, int height);
	void setWindow(RenderWindow* window);
	std::vector<std::vector<char>> create();
	std::vector<std::vector<char>> get();

};