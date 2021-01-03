#include "RenderWindow.h"

RenderWindow::RenderWindow(Camera* p_cam) :window(NULL), renderer(NULL), cam(p_cam){
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(bordered == 0) SDL_SetWindowBordered(window, SDL_FALSE);

	nothing = loadTexture(nothingTexture);
	water = loadTexture(waterTexture);
	dirt = loadTexture(dirtTexture);
	grass = loadTexture(grassTexture);
	playerTex = loadTexture(playerTexture);
}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}

inline SDL_Texture* RenderWindow::getTexture(char id) {
	switch (id) {
	case NOTHING:
		return nothing;
	case WATER:
		return water;
	case DIRT:
		return dirt;
	case GRASS:
		return grass;
	default:
		return nothing;
	}
}

void RenderWindow::handleWindow(SDL_Event* event) {
	if (event->key.keysym.sym == SDLK_p && event->type == SDL_KEYDOWN /*&& !fullScreen*/) {
		if (bordered) SDL_SetWindowBordered(window, SDL_FALSE);
		else SDL_SetWindowBordered(window, SDL_TRUE);
		bordered = !bordered;
	}

	/* if (event->key.keysym.sym == SDLK_o && event->type == SDL_KEYDOWN) {
		if (fullScreen) {
			SDL_SetWindowFullscreen(window, SDL_FALSE);
		}
		else {
			if (bordered) {
				SDL_SetWindowBordered(window, SDL_FALSE);
				bordered = !bordered;
			}
			SDL_SetWindowFullscreen(window, SDL_TRUE);
		}
		fullScreen = !fullScreen;
	} */
}

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::destroy() { SDL_DestroyWindow(window); }

void RenderWindow::render(Entity* p_entity) {
	SDL_Rect dst{ (int)(p_entity->getX() - cam->x), (int)(p_entity->getY() - cam->y), p_entity->getCurrentFrame()->w * SCALE, p_entity->getCurrentFrame()->h * 4};
		SDL_RenderCopy(renderer, getTexture(p_entity->getTextureID()), p_entity->getCurrentFrame(), &dst);
}

void RenderWindow::render(Player* p_entity, bool lastRight) {
	SDL_Rect dst{ (int)(p_entity->getX() - cam->x), (int)(p_entity->getY() - cam->y), p_entity->getCurrentFrame()->w * SCALE, p_entity->getCurrentFrame()->h * 4 };

	if(!lastRight) SDL_RenderCopyEx(renderer, playerTex, p_entity->getCurrentFrame(), &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
	else if(lastRight) SDL_RenderCopy(renderer, playerTex, p_entity->getCurrentFrame(), &dst);
}

void RenderWindow::render(std::vector<std::vector<Entity>>* map) {
	for(std::vector<Entity> row : *map)
		for (Entity tile : row) render(&tile);
}