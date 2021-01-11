#pragma once
#include <string>

// Very usefull
const bool jiriSmrdi = 1;
const bool jiriSeUmyl = 0;

// Loop Types
const char ESCAPE = 0;
const char MENU = 1;
const char LEVEL = 2;
const char PAUSE = 3;

// Seeds
const std::string seed = "B";

// Textures
const int NOTHING = 0;
const char nothingTexture[] = "textures/nothing.png";
const int WATER = 1;
const char waterTexture[] = "textures/water.png";
const int DIRT = 2;
const char dirtTexture[] = "textures/dirt.png";
const int GRASS = 3;
const char grassTexture[] = "textures/grass.png";
const int PLAYER = 4;
const char playerTexture[] = "textures/player.png";

// FPS Handling
const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int SCALE = 4; // Scale

// Position constants
const float screenRatio = 2;
const int tileSize = 32 * SCALE;
const int screenMapRatio = 3;
const int screenTileCountHeight = 7;
const int screenTileCountWidth = (int)(screenTileCountHeight * screenRatio);
const int mapTileCountWidth = screenTileCountWidth * screenMapRatio;
const int mapTileCountHeight = screenTileCountHeight * screenMapRatio;
const int screenWidth = screenTileCountWidth * tileSize;
const int screenHeight = screenTileCountHeight * tileSize;
const int mapSizeWidth = mapTileCountWidth * tileSize;
const int mapSizeHeight = mapTileCountHeight * tileSize;

// Player attributes
const float speed = 5;