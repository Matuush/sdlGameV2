#pragma once
#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "Camera.h"

#include "Constants.h"

struct RenderWindow {
	const char* title = "SDL Moment";
	bool /* fullScreen = 0,*/ bordered = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* cam;

	SDL_Texture* nothing;
	SDL_Texture* water;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* playerTex;

	RenderWindow() = default;
	RenderWindow(Camera* p_cam);

	SDL_Texture* loadTexture(const char* path);
	inline SDL_Texture* getTexture(char id);

	void handleWindow(SDL_Event* event);
	void clear();
	void display();
	void destroy();

	void render(Player* p_entity, bool lastRight);
	void render(Entity* p_entity);
	void render(std::vector<std::vector<Entity>>* map);
};