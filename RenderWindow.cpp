#include "RenderWindow.h"

bool RenderWindow::paused = 0;
bool RenderWindow::windowType = 1;
RenderWindow::RenderWindow(Camera* p_cam) :window(NULL), renderer(NULL), cam(p_cam){
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL) std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	textures.push_back(IMG_LoadTexture(renderer, nothingTexture.path)); // 0
	textures.push_back(IMG_LoadTexture(renderer, waterTexture.path)); // 1
	textures.push_back(IMG_LoadTexture(renderer, dirtTexture.path)); // 2
	textures.push_back(IMG_LoadTexture(renderer, grassTexture.path)); // 3
	textures.push_back(IMG_LoadTexture(renderer, playerTexture.path)); // 4
	textures.push_back(IMG_LoadTexture(renderer, buttonTexture.path)); // 5
	textures.push_back(IMG_LoadTexture(renderer, backgroundTexture.path)); // 6

	TTF_Init(); // Text
}

void RenderWindow::handleWindow() {
	if (windowType == FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_TRUE);
	else SDL_SetWindowFullscreen(window, SDL_FALSE);
	if (windowType == BORDERLESS) SDL_SetWindowBordered(window, SDL_FALSE);
	else if (windowType == BORDERED) SDL_SetWindowBordered(window, SDL_TRUE);
}

void RenderWindow::clear() { SDL_RenderClear(renderer); }

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::destroy() { SDL_DestroyWindow(window); }

void RenderWindow::render(Entity* p_entity) {
	SDL_Rect dst{ (int)(p_entity->position.x - cam->x), (int)(p_entity->position.y - cam->y), p_entity->currentFrame.w * SCALE, p_entity->currentFrame.h * SCALE};

	SDL_Texture* tempTex = textures[p_entity->textureID];
	if (paused) SDL_SetTextureColorMod(tempTex, 100, 100, 100);
	else SDL_SetTextureColorMod(tempTex, 255, 255, 255);

	if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, &p_entity->currentFrame, &dst); 
	else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, &p_entity->currentFrame, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void RenderWindow::freeRender(Button* p_entity) {
	SDL_Rect dst{ (int)(p_entity->position.x), (int)(p_entity->position.y), p_entity->w, p_entity->h };
	SDL_RenderCopy(renderer, textures[p_entity->textureID], /*p_entity->getCurrentFrame()*/ NULL, &dst);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(p_entity->font, p_entity->text, p_entity->color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	dst = { (int)(p_entity->position.x + SCALE), (int)(p_entity->position.y + (double)SCALE), (int)(p_entity->w - 2 * (double)SCALE), (int)(p_entity->h - 2 * (double)SCALE)};
	SDL_RenderCopy(renderer, message, NULL, &dst);
	SDL_DestroyTexture(message);
}

void RenderWindow::renderBackground() {
	SDL_Texture* tempTex = textures[backgroundTexture.id];
	SDL_SetTextureColorMod(tempTex, 255, 0, 255);
	if(paused)SDL_SetTextureAlphaMod(tempTex, 100);
	else SDL_SetTextureAlphaMod(tempTex, 255);

	SDL_Rect dst{ 0, 0, screenWidth, screenHeight };
	SDL_RenderCopy(renderer, tempTex, NULL, &dst);
}