#pragma once
#include "SDL2/SDL_image.h"
#include "data/Camera.hpp"
#include "Button.hpp"

enum WINDOW_TYPE : unsigned char { BORDERLESS, BORDERED, FULLSCREEN };

class RenderWindow {
public:
	static bool paused, renderColliders;
	static WINDOW_TYPE windowType;

	Camera* cam = new Camera();

	RenderWindow() :window(NULL), renderer(NULL) {
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		createTexture(NOTHING_TEXTURE);
		createTexture(WATER_TEXTURE);
		createTexture(DIRT_TEXTURE);
		createTexture(GRASS_TEXTURE);
		createTexture(PLAYER_TEXTURE);
		createTexture(ENEMY_TEXTURE);
		createTexture(BUTTON_TEXTURE);
		createTexture(BACKGROUND_TEXTURE);
		createTexture(BULLET_TEXTURE);

		TTF_Init();
		defaultFont = TTF_OpenFont("textures/font/slkscr.ttf", 32);
	}

	void clear() { SDL_RenderClear(renderer); }
	void display() { SDL_RenderPresent(renderer); }
	void destroy() { SDL_DestroyWindow(window); }

	void handleWindow() {
		if (windowType == FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_TRUE);
		else SDL_SetWindowFullscreen(window, SDL_FALSE);
		if (windowType == BORDERLESS) SDL_SetWindowBordered(window, SDL_FALSE);
		else if (windowType == BORDERED) SDL_SetWindowBordered(window, SDL_TRUE);
	}
	void render(Entity* p_entity) {
		if (p_entity->display) {
			SDL_Rect dst{ (int)(p_entity->position.x - cam->position.x), (int)(p_entity->position.y - cam->position.y), p_entity->currentFrame.w * SCALE, p_entity->currentFrame.h * SCALE };

			SDL_Texture* tempTex = textures[p_entity->texture.id];
			if (paused) SDL_SetTextureColorMod(tempTex, 100, 100, 100);
			else  SDL_SetTextureColorMod(tempTex, 255, 255, 255);

			if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, &p_entity->currentFrame, &dst);
			else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, &p_entity->currentFrame, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);

			if (renderColliders) renderCollider(p_entity);
		}
	}
	void render(Creature* p_entity) {
		if (p_entity->display) {
			SDL_Rect dst{ (int)(p_entity->position.x - cam->position.x), (int)(p_entity->position.y - cam->position.y), p_entity->currentFrame.w * SCALE, p_entity->currentFrame.h * SCALE };

			SDL_Texture* tempTex = textures[p_entity->texture.id];
			if(p_entity->hurtTimer > 2){SDL_SetTextureColorMod(tempTex, 255, 255 - p_entity->hurtTimer, 255 - p_entity->hurtTimer); p_entity->hurtTimer -= 2;}
			if (paused) SDL_SetTextureColorMod(tempTex, 100, 100, 100);
			else if(p_entity->hurtTimer <= 0) SDL_SetTextureColorMod(tempTex, 255, 255, 255);

			if (p_entity->lastRight) SDL_RenderCopy(renderer, tempTex, &p_entity->currentFrame, &dst);
			else if (!p_entity->lastRight) SDL_RenderCopyEx(renderer, tempTex, &p_entity->currentFrame, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
			
			SDL_SetTextureColorMod(tempTex, 255, 255, 255);

			if (renderColliders) renderCollider(p_entity);
		}
	}
	void renderButton(Button* p_entity) {
		SDL_Texture* tempSex = textures[p_entity->texture.id];
		if (!p_entity->unlocked) SDL_SetTextureColorMod(tempSex, 150, 0, 0);
		else SDL_SetTextureColorMod(tempSex, 255, 255, 255);

		SDL_Rect dst{ (int)(p_entity->position.x), (int)(p_entity->position.y), (int)p_entity->w, (int)p_entity->h };
		
		SDL_RenderCopy(renderer, tempSex, &p_entity->currentFrame, &dst);
		
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(defaultFont, p_entity->text, p_entity->color);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
		
		dst = { (int)p_entity->position.x + SCALE + buttonMargin, (int)p_entity->position.y + SCALE + buttonMargin, 
		p_entity->w - 2 * SCALE - 2 * buttonMargin, p_entity->h - 2 * SCALE - 2 * buttonMargin};
		SDL_RenderCopy(renderer, message, NULL, &dst);
		SDL_DestroyTexture(message);
	}
	void renderBackground() {
		SDL_Texture* tempTex = textures[BACKGROUND_TEXTURE.id];
		SDL_SetTextureColorMod(tempTex, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b);
		if (paused)SDL_SetTextureAlphaMod(tempTex, 100);
		else SDL_SetTextureAlphaMod(tempTex, 255);

		SDL_Rect dst{ 0, 0, (int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y };
		SDL_RenderCopy(renderer, tempTex, NULL, &dst);
	}

	void displayStats(std::vector<Creature*> creatures) {
		for (int i = 0; i < creatures.size(); i++) {
			const std::string textPos = "creature" + std::to_string(i + 1) + " hp: " + std::to_string((int)creatures[i]->health);
			SDL_Rect dst = { (int)(SCREEN_SIZE.x - TILE_SIZE * 3), i * TILE_SIZE, TILE_SIZE * 3, TILE_SIZE };
			renderText(textPos.c_str(), dst);
		}
	}
	void DrawCircle(Vector2D centre, int32_t radius) {
		const int32_t diameter = (radius * 2);

		int32_t x = (radius - 1), y = 0;
		int32_t tx = 1, ty = 1;
		int32_t error = (tx - diameter);

		while (x >= y) {
			SDL_RenderDrawPoint(renderer, (int)centre.x + x, (int)centre.y - y);
			SDL_RenderDrawPoint(renderer, (int)centre.x + x, (int)centre.y + y);
			SDL_RenderDrawPoint(renderer, (int)centre.x - x, (int)centre.y - y);
			SDL_RenderDrawPoint(renderer, (int)centre.x - x, (int)centre.y + y);
			SDL_RenderDrawPoint(renderer, (int)centre.x + y, (int)centre.y - x);
			SDL_RenderDrawPoint(renderer, (int)centre.x + y, (int)centre.y + x);
			SDL_RenderDrawPoint(renderer, (int)centre.x - y, (int)centre.y - x);
			SDL_RenderDrawPoint(renderer, (int)centre.x - y, (int)centre.y + x);

			if (error <= 0) {
				++y;
				error += ty;
				ty += 2;
			}

			else {
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* defaultFont;
	SDL_Texture* textures[8];

	const int buttonMargin = 30;

	inline void renderText(const char* text, SDL_Rect dst){
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(defaultFont, text, DEFAULT_TEXT_COLOR);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);

		SDL_RenderCopy(renderer, message, NULL, &dst);
		SDL_DestroyTexture(message);
	}

	inline void renderCollider(Entity* p_entity) {
		if (p_entity->solid)SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		for(Collider* col : p_entity->colliders.colliders){
			switch(col->type) {
				case RECTANGLE:{
					SDL_Rect colsrc = {(int)(col->position.x - cam->position.x), (int)(col->position.y - cam->position.y), (int)col->size.x, (int)col->size.y};
					SDL_RenderDrawRect(renderer, &colsrc);
					break;
				}
				case CIRCLE:
					DrawCircle(col->position - cam->position, col->radius);
					break;
			}
		}
		if (p_entity->solid) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	inline void createTexture(Texture p_texture) {
		textures[p_texture.id] = IMG_LoadTexture(renderer, p_texture.path);
	}
};