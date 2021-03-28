#pragma once
#include <string>
#include "Vector2D.h"
#include "Texture.h"
#include "RectangleCollider.h"

// Very usefull
const bool JIRI_SMRDI = 1;
const bool JIRI_SE_UMYL = 0;

enum LOOP_TYPE : unsigned char { ESCAPE, MENU, LEVEL, PAUSE, LEVEL_SELECTOR };
enum WINDOW_TYPE : unsigned char { BORDERLESS, BORDERED, FULLSCREEN };

// GUI
const char TITLE[] = "SDL Moment";
const std::string SEED = "B";
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
const SDL_Color DEFAULT_TEXT_COLOR = { 255, 255, 255 };
const SDL_Color BACKGROUND_COLOR = { 0, 255, 0 };

// Texture sizes
const int SCALE = 4;
const int RAW_TILE = 32;
const int RAW_PLAYER = 64;
const int RAW_ENEMY = 64;

// Textures
const Texture NOTHING_TEXTURE(0, "textures/nothing.png", RAW_TILE);
const Texture WATER_TEXTURE(1, "textures/water.png", RAW_TILE);
const Texture DIRT_TEXTURE(2, "textures/dirt.png", RAW_TILE);
const Texture GRASS_TEXTURE(3, "textures/grass.png", RAW_TILE);
const Texture PLAYER_TEXTURE(4, "textures/kapusta.png", RAW_PLAYER);
const Texture BUTTON_TEXTURE(5, "textures/button.png", RAW_TILE * 2, RAW_TILE);
const Texture BACKGROUND_TEXTURE(6, "textures/background.png");
const Texture ENEMY_TEXTURE = PLAYER_TEXTURE;

// Map constants
const int TILE_SIZE = RAW_TILE * SCALE;
const int SCREEN_RATIO = 2;
const int SCREEN_MAP_RATIO = 3;
const int SCREEN_TILE_COUNT_Y = 7;
const Vector2D SCREEN_TILE_COUNT = Vector2D(SCREEN_TILE_COUNT_Y * SCREEN_RATIO, SCREEN_TILE_COUNT_Y);
const Vector2D SCREEN_SIZE = SCREEN_TILE_COUNT * TILE_SIZE;
const Vector2D MAP_TILE_COUNT = SCREEN_TILE_COUNT * SCREEN_MAP_RATIO;
const Vector2D MAP_SIZE = MAP_TILE_COUNT * TILE_SIZE;
const int BORDER_THICKNESS = 100;

// Button constants
const Vector2D BUTTON_SIZE = Vector2D(TILE_SIZE * 4, TILE_SIZE * 2);
const SDL_Color PASSIVE_BUTTON_TEXT_COLOR = { 0, 0, 0 };
const SDL_Color ACTIVE_BUTTON_TEXT_COLOR = { 50, 50, 50 };

// Entity constants
const double DEFAULT_TERMINAL_VELOCITY = 2 * (double)SCALE;

// Player attributes
const double PLAYER_VELOCITY = DEFAULT_TERMINAL_VELOCITY;
const double PLAYER_TERMINAL_VELOCITY = 500 * SCALE;
const double DEFAULT_PLAYER_HEALTH = 50;
const double DEFAULT_PLAYER_DAMAGE = 5;
RectangleCollider kapustaColliders[17] = {
	RectangleCollider(12, 13, 32, 32) * SCALE,
	RectangleCollider(11, 13, 1, 24) * SCALE,
	RectangleCollider(19, 45, 24, 5) * SCALE,
	RectangleCollider(44, 19, 8, 25) * SCALE,
	RectangleCollider(31, 10, 11, 3) * SCALE,
	RectangleCollider(32, 7, 5, 3) * SCALE,
	RectangleCollider(52, 24, 2, 17) * SCALE,
	RectangleCollider(54, 28, 2, 8) * SCALE,
	RectangleCollider(44, 44, 6, 2) * SCALE,
	RectangleCollider(43, 46, 4, 2) * SCALE,
	RectangleCollider(44, 17, 6, 2) * SCALE,
	RectangleCollider(44, 15, 3, 2) * SCALE,
	RectangleCollider(16, 45, 3, 3) * SCALE,
	RectangleCollider(14, 11, 7, 2) * SCALE,
	RectangleCollider(17, 9, 4, 2) * SCALE,
	RectangleCollider(10, 19, 1, 13) * SCALE,
	RectangleCollider(36, 50, 6, 1) * SCALE
};

// Enemy attributes
const double DEFAULT_ENEMY_HEALTH = 50;
const double DEFAULT_ENEMY_DAMAGE = 5;
const double DEFAULT_ENEMY_TERMINAL_VELOCITY = DEFAULT_TERMINAL_VELOCITY / 2;