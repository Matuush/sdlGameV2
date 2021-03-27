#pragma once
#include "SDL/SDL_image.h"
#include "Camera.h"
#include "Button.h"

class RenderWindow {
public:
	static bool paused, renderColliders;
	static char windowType;

	Camera* cam = new Camera();

	RenderWindow() :window(NULL), renderer(NULL) {
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE.x,
			SCREEN_SIZE.y, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		textures[0] = IMG_LoadTexture(renderer, NOTHING_TEXTURE.path);
		textures[1] = IMG_LoadTexture(renderer, WATER_TEXTURE.path);
		textures[2] = IMG_LoadTexture(renderer, DIRT_TEXTURE.path);
		textures[3] = IMG_LoadTexture(renderer, GRASS_TEXTURE.path);
		textures[4] = IMG_LoadTexture(renderer, PLAYER_TEXTURE.path);
		textures[5] = IMG_LoadTexture(renderer, BUTTON_TEXTURE.path);
		textures[6] = IMG_LoadTexture(renderer, BACKGROUND_TEXTURE.path);

		TTF_Init(); // Text
		defaultFont = TTF_OpenFont("textures/Sans.ttf", 24);
	}

	void handleWindow() {
		if (windowType == FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_TRUE);
		else SDL_SetWindowFullscreen(window, SDL_FALSE);
		if (windowType == BORDERLESS) SDL_SetWindowBordered(window, SDL_FALSE);
		else if (windowType == BORDERED) SDL_SetWindowBordered(window, SDL_TRUE);
	}
	void clear() { SDL_RenderClear(renderer); }
	void display() { SDL_RenderPresent(renderer); }
	void destroy() { SDL_DestroyWindow(window); }

	void render(Entity* p_entity) {
		SDL_Rect dst{ (int)(p_entity->position.x - cam->x), (int)(p_entity->position.y - cam->y), p_entity->currentFrame.w * SCALE, p_entity->currentFrame.h * SCALE };

		SDL_Texture* tempTex = textures[p_entity->textureID];
		if (paused) SDL_SetTextureColorMod(tempTex, 100, 100, 100);
		else SDL_SetTextureColorMod(tempTex, 255, 255, 255);

		if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, &p_entity->currentFrame, &dst);
		else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, &p_entity->currentFrame, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);

		if (renderColliders) renderCollider(p_entity);
	}
	void freeRender(Button* p_entity) {
		SDL_Rect dst{ (int)(p_entity->position.x), (int)(p_entity->position.y), (int)p_entity->w, (int)p_entity->h };
		SDL_RenderCopy(renderer, textures[p_entity->textureID], &p_entity->currentFrame, &dst);

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(defaultFont, p_entity->text, p_entity->color);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);

		dst = { (int)(p_entity->position.x + SCALE), (int)(p_entity->position.y + (double)SCALE), (int)(p_entity->w - 2 * (double)SCALE), (int)(p_entity->h - 2 * (double)SCALE) };
		SDL_RenderCopy(renderer, message, NULL, &dst);
		SDL_DestroyTexture(message);
	}
	void renderBackground() {
		SDL_Texture* tempTex = textures[BACKGROUND_TEXTURE.id];
		SDL_SetTextureColorMod(tempTex, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b);
		if (paused)SDL_SetTextureAlphaMod(tempTex, 100);
		else SDL_SetTextureAlphaMod(tempTex, 255);

		SDL_Rect dst{ 0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y };
		SDL_RenderCopy(renderer, tempTex, NULL, &dst);
	}

	void displayStats(std::vector<Player*> players) {
		for (int i = 0; i < players.size(); i++) {
			const std::string textPos = "x: " + std::to_string((int)players[i]->position.x) + " y: " + std::to_string((int)players[i]->position.y);
			SDL_Surface* surfaceMessage = TTF_RenderText_Solid(defaultFont, textPos.c_str(), DEFAULT_TEXT_COLOR);
			SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);

			SDL_Rect dst = { SCREEN_SIZE.x - TILE_SIZE * 2, i * TILE_SIZE, TILE_SIZE * 2, TILE_SIZE };
			SDL_RenderCopy(renderer, message, NULL, &dst);
			SDL_DestroyTexture(message);
		}
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* defaultFont;
	SDL_Texture* textures[7];

	inline void renderCollider(Entity* p_entity) {
	if (p_entity->solid) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (const auto& c : p_entity->colliders) {
		SDL_Rect colsrc = { (int)(c.x - cam->x), (int)(c.y - cam->y), (int)c.w, (int)c.h };
		SDL_RenderDrawRect(renderer, &colsrc);
	}
	if (p_entity->solid) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
};