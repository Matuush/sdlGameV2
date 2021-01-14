#include "RenderWindow.h"

bool RenderWindow::paused = 0;
bool RenderWindow::bordered = 0;
RenderWindow::RenderWindow(Camera* p_cam) :window(NULL), renderer(NULL), cam(p_cam){
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(bordered == 0) SDL_SetWindowBordered(window, SDL_FALSE);

	textures.push_back(loadTexture(nothingTexture)); // 0
	textures.push_back(loadTexture(waterTexture)); // 1
	textures.push_back(loadTexture(dirtTexture)); // 2
	textures.push_back(loadTexture(grassTexture)); // 3
	textures.push_back(loadTexture(playerTexture)); // 4
	textures.push_back(loadTexture(buttonTexture)); // 5
	textures.push_back(loadTexture(backgroundTexture)); // 6

	TTF_Init();

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
}

inline SDL_Texture* RenderWindow::loadTexture(const char* path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::handleWindow() {
		if (bordered == BORDERLESS) SDL_SetWindowBordered(window, SDL_FALSE);
		else if(bordered == BORDERED)SDL_SetWindowBordered(window, SDL_TRUE);

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
	SDL_Rect dst{ (int)(p_entity->getX() - cam->x), (int)(p_entity->getY() - cam->y), p_entity->getCurrentFrame()->w * SCALE, p_entity->getCurrentFrame()->h * SCALE};

	SDL_Texture* tempTex = textures[p_entity->getTextureID()];
	if (paused) SDL_SetTextureColorMod(tempTex, 100, 100, 100);
	else SDL_SetTextureColorMod(tempTex, 255, 255, 255);

	if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, p_entity->getCurrentFrame(), &dst); 
	else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, p_entity->getCurrentFrame(), &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void RenderWindow::render(std::vector<std::vector<Entity>>* map) {
	for(std::vector<Entity> row : *map)
		for (Entity tile : row) render(&tile);
}

void RenderWindow::freeRender(Button* p_entity) {
	SDL_Rect dst{ (int)(p_entity->collider.x), (int)(p_entity->collider.y), p_entity->collider.w, p_entity->collider.h };
	SDL_RenderCopy(renderer, textures[p_entity->getTextureID()], p_entity->getCurrentFrame(), &dst);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(p_entity->font, p_entity->text, p_entity->color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	dst = { (int)(p_entity->collider.x + 1 * SCALE), (int)(p_entity->collider.y + 1 * SCALE), (int)(p_entity->collider.w - 2 * SCALE), (int)(p_entity->collider.h - 2 * SCALE)};
	SDL_RenderCopy(renderer, message, NULL, &dst);
	SDL_DestroyTexture(message);
}

void RenderWindow::renderBackground(Entity* p_entity) {
	SDL_Rect dst{ (int)(p_entity->getX()), (int)(p_entity->getY()), screenWidth, screenHeight };

	SDL_Texture* tempTex = textures[p_entity->getTextureID()];
	SDL_SetTextureColorMod(tempTex, 255, 0, 255);
	if(paused)SDL_SetTextureAlphaMod(tempTex, 100);
	else SDL_SetTextureAlphaMod(tempTex, 255);

	if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, NULL, &dst);
	else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}