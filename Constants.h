#pragma once
#include <string>
#include "Texture.h"

// Very usefull
const bool jiriSmrdi = 1;
const bool jiriSeUmyl = 0;

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
const char TITLE[] = "SDL Moment";

// Seed
const std::string seed = "B";

const int SCALE = 4; // Scale

// Texture sizes
const int rawTile = 32;
const int rawPlayer = 64;

// Position constants
const double screenRatio = 2;
const int tileSize = rawTile * SCALE;
const int screenMapRatio = 3;
const int screenTileCountHeight = 7;
const int screenTileCountWidth = (int)(screenTileCountHeight * screenRatio);
const int mapTileCountWidth = screenTileCountWidth * screenMapRatio;
const int mapTileCountHeight = screenTileCountHeight * screenMapRatio;
const int screenWidth = screenTileCountWidth * tileSize;
const int screenHeight = screenTileCountHeight * tileSize;
const int mapSizeWidth = mapTileCountWidth * tileSize;
const int mapSizeHeight = mapTileCountHeight * tileSize;
const int buttonHeight = tileSize * 2;
const int buttonWidth = buttonHeight * 2;

// Textures
const Texture nothingTexture(0, "textures/nothing.png", rawTile);
const Texture waterTexture(1, "textures/water.png", rawTile);
const Texture dirtTexture(2, "textures/dirt.png", rawTile);
const Texture grassTexture(3, "textures/grass.png", rawTile);
const Texture playerTexture(4, "textures/player.png", rawPlayer);
const Texture buttonTexture(5, "textures/button.png", rawTile * 2, rawTile);
const Texture backgroundTexture(6, "textures/background.png");

// FPS Handling
const int FPS = 60;
const int frameDelay = 1000 / FPS;

// Player attributes
const double SPEED = 1.5 * SCALE;
const int playerHitboxDistanceX = 24;
const int playerHitboxDistanceY = 22;
const int playerHitboxWidth = 16;
const int playerHitboxHeight = 28;

// Constants
const int floatPrecision = 8;