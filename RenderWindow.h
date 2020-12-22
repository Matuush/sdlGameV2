#pragma once
#include <SDL.h>

#include "Entity.h"
#include "Player.h"
#include "Camera.h"
#include "Constants.h"

struct RenderWindow {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera* cam;

	RenderWindow() = default;
	RenderWindow(const char* p_title, Camera* p_cam);

	void clear();
	void display();
	void destroy();

	SDL_Texture* loadTexture(const char* p_filePath);

	void render(Entity* p_entity);
	void renderFlip(Entity* p_entity);
};