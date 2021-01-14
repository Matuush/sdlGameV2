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
	const char* title = "SDL Moment";
	/*bool  fullScreen = 0,*/ 
	static bool paused, bordered;

	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* cam;

	std::vector<SDL_Texture*> textures;

	RenderWindow() = default;
	RenderWindow(Camera* p_cam);

	inline SDL_Texture* loadTexture(const char* path);

	void handleWindow();
	void clear();
	void display();
	void destroy();

	void render(Entity* p_entity);
	void render(std::vector<std::vector<Entity>>* map);
	void freeRender(Button* p_entity);
	void renderBackground(Entity* p_entity);
};