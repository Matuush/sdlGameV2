#pragma once
#include <string>

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
const int BUTTON = 5;
const char buttonTexture[] = "textures/button.png";
const int BACKGROUND = 6;
const char backgroundTexture[] = "textures/background.png";

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
const int buttonHeight = tileSize * 2;
const int buttonWidth = buttonHeight * 2;

// Player attributes
const float SPEED = 1.5 * SCALE;
const int playerHitboxDistanceX = 24;
const int playerHitboxDistanceY = 22;
const int playerHitboxWidth = 16;
const int playerHitboxHeight = 28;