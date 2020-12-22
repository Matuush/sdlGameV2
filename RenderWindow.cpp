#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, Camera* p_cam) :window(NULL), renderer(NULL), cam(p_cam){
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if(window == NULL) std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if (texture == NULL) std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::destroy() { SDL_DestroyWindow(window); }

void RenderWindow::render(Entity* p_entity) {
	SDL_Rect dst{ (int)(p_entity->getX() - cam->x), (int)(p_entity->getY() - cam->y), p_entity->getCurrentFrame()->w * SCALE, p_entity->getCurrentFrame()->h * 4};
	SDL_RenderCopy(renderer, p_entity->getTexture(), p_entity->getCurrentFrame(), &dst);
}

void RenderWindow::renderFlip(Entity* p_entity) {
	SDL_Rect dst{ (int)(p_entity->getX() - cam->x), (int)(p_entity->getY() - cam->y), p_entity->getCurrentFrame()->w * SCALE, p_entity->getCurrentFrame()->h * 4};

	SDL_RenderCopyEx(renderer, p_entity->getTexture(), p_entity->getCurrentFrame(), &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}