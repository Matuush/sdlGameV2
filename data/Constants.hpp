#pragma once
#include <string>
#include "Vector2D.hpp"
#include "Texture.hpp"
#include "../Collider.hpp"

// Very useful
const bool JIRI_SMRDI = 1;
const bool JIRI_SE_UMYL = 0;

// Types
enum LOOP_TYPE : unsigned char { ESCAPE, MENU, LEVEL, PAUSE, LEVEL_SELECTOR, SETTINGS };

// GUI
const char TITLE[] = "SDL Moment";
const std::string SEED = "B";
const unsigned char FPS = 60;
const unsigned char FRAME_DELAY = 1000 / FPS;
const SDL_Color DEFAULT_TEXT_COLOR = { 255, 255, 255 };
const SDL_Color BACKGROUND_COLOR = { 0, 255, 0 };

// Texture sizes
const int SCALE = 4;
const int RAW_TILE = 32;
const int RAW_PLAYER = 64;
const int RAW_ENEMY = 64;

// Textures
const Texture NOTHING_TEXTURE("textures/nothing.png", RAW_TILE);
const Texture WATER_TEXTURE("textures/water.png", RAW_TILE);
const Texture DIRT_TEXTURE("textures/dirt.png", RAW_TILE);
const Texture GRASS_TEXTURE("textures/grass.png", RAW_TILE);
const Texture PLAYER_TEXTURE("textures/kapusta.png", RAW_PLAYER);
const Texture ENEMY_TEXTURE = PLAYER_TEXTURE;
const Texture BUTTON_TEXTURE("textures/button.png", RAW_TILE * 2, RAW_TILE);
const Texture BACKGROUND_TEXTURE("textures/background.png");
const Texture BULLET_TEXTURE("textures/bullet.png", 4, 4);

// Map attributes
const int TILE_SIZE = RAW_TILE * SCALE;
const unsigned int SCREEN_RATIO = 2;
const unsigned int SCREEN_MAP_RATIO = 3;
const unsigned int SCREEN_TILE_COUNT_Y = 7;
const Vector2D SCREEN_TILE_COUNT = Vector2D(SCREEN_TILE_COUNT_Y * SCREEN_RATIO, SCREEN_TILE_COUNT_Y);
const Vector2D SCREEN_SIZE = SCREEN_TILE_COUNT * TILE_SIZE;
const Vector2D MAP_TILE_COUNT = SCREEN_TILE_COUNT * SCREEN_MAP_RATIO;
const Vector2D MAP_SIZE = MAP_TILE_COUNT * TILE_SIZE;
const int BORDER_THICKNESS = 1000;

// Button attributes
const Vector2D BUTTON_SIZE = Vector2D(TILE_SIZE * 4, TILE_SIZE * 2);
const SDL_Color PASSIVE_BUTTON_TEXT_COLOR = { 0, 0, 0 };
const SDL_Color ACTIVE_BUTTON_TEXT_COLOR = { 50, 50, 50 };
const SDL_Color LOCKED_BUTTON_TEXT_COLOR = { 255, 0, 0 };

// Entity attributes
const double DEFAULT_TERMINAL_VELOCITY = 2 * (double)SCALE;
const double FRICTION = 0.05;
const unsigned int KAPUSTA_WIDTH = 80;

// Player attributes
const double PLAYER_VELOCITY = DEFAULT_TERMINAL_VELOCITY / 7;
const double PLAYER_TERMINAL_VELOCITY = 500 * SCALE;
const double DEFAULT_PLAYER_HEALTH = 50;
const double DEFAULT_PLAYER_DAMAGE = 5;

// Bullet attributes
const Vector2D DEFAULT_BULLET_POSITION(-10, -10);
const double DEFAULT_BULLET_TERMINAL_VELOCITY = DEFAULT_TERMINAL_VELOCITY * 7;
const unsigned int BULLET_WIDTH = 8;

// Enemy attributes
const double DEFAULT_ENEMY_HEALTH = 50;
const double DEFAULT_ENEMY_DAMAGE = 5;
const double DEFAULT_ENEMY_TERMINAL_VELOCITY = DEFAULT_TERMINAL_VELOCITY;