#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "UdpCom.h"

#include "RenderWindow.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Button.h"
#include "Entity.h"
#include "Level.h"

#include "Constants.h"

class Game {
private:
	const char* ip = "10.49.0.6";
	int port = 80;

	Camera cam = Camera();
	RenderWindow* window = new RenderWindow(&cam);

	std::vector<Button> menuButtons;
	std::vector<Button> pauseButtons;

public:
	static char loopType;

	Game();

	void theLoop();
	inline void menu();
	inline void level();
	inline void pause();

	void end();
};