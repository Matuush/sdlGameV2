#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Button.h"

#include "Constants.h"
class Game {
private:
	Map map;
	Camera cam;
	RenderWindow* window = new RenderWindow(&cam);

	std::vector<Player> players;
	
	char loopType;

public:
	Game();

	void theLoop();
	inline void menu();
	inline void level();
	inline void pause();

	void end();
};