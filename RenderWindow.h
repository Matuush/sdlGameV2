#pragma once
#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Entity.h"
#include "Camera.h"
#include "Button.h"

#include "Constants.h"

struct RenderWindow {
	static bool paused, renderColliders;
	static char windowType;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* cam;

	TTF_Font* defaultFont;

	std::vector<SDL_Texture*> textures;

	RenderWindow() = default;
	RenderWindow(Camera* p_cam);

	void handleWindow();
	void clear();
	void display();
	void destroy();

	void render(Entity* p_entity);
	inline void renderCollider(Entity* p_entity);
	void freeRender(Button* p_entity);
	void renderBackground();

	void displayStats(Player* p_entity);
};