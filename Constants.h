#pragma once
#include <string>

const std::string seed = "B";

const char nothingTexture[] = "textures/nothing.png";
const char waterTexture[] = "textures/water.png";
const char dirtTexture[] = "textures/dirt.png";
const char grassTexture[] = "textures/grass.png";

const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int SCALE = 4;

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

const float speed = 5;