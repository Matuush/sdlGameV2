#pragma once
#include <string>
#include "Vector2D.h"
#include "Texture.h"

// Very usefull
const bool JIRI_SMRDI = 1;
const bool JIRI_SE_UMYL = 0;

// Loop types
const char ESCAPE = 0;
const char MENU = 1;
const char LEVEL = 2;
const char PAUSE = 3;

// Window types
const char BORDERLESS = 0;
const char BORDERED = 1;
const char FULLSCREEN = 2;

// GUI
const char TITLE[] = "SDL Mement";
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
// Temporary player hitbox
const Vector2D PLAYER_HITBOX_DISTANCE = Vector2D(24 * SCALE, 22 * SCALE);
const Vector2D PLAYER_HITBOX_SIZE = Vector2D(16 * SCALE, 28 * SCALE);

// Enemy attributes
const double defaultEnemyHealth = 50;
const double defaultEnemyDamage = 5;
const double defaultEnemyTerminalVelocity = DEFAULT_TERMINAL_VELOCITY / 2;
// Temporary enemy hitbox
const Vector2D enemyHitboxDistance = PLAYER_HITBOX_DISTANCE;
const Vector2D enemyHitboxSize = PLAYER_HITBOX_SIZE;