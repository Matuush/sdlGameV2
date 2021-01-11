#include "GameManager.h"

Game::Game() {
	UdpCom::start(); // Server
	UdpCom com(ip, 80);

	com.send("{ \"id\":\"da big chungus\" }");

	loopType = MENU;

	Map tempMap(window); // Map
	map = tempMap;

	// Players
	Player player(10.0f, 10.0f, &map.tileMap);
	players.push_back(player);

	// Pause buttons
	Button playButton(screenWidth / 4 - 200, screenHeight / 2 - 100, "play", LEVEL);
	pauseButtons.push_back(playButton);
	Button escapeButton(3 * screenWidth / 4 - 200, screenHeight / 2 - 100, "exit", ESCAPE);
	pauseButtons.push_back(escapeButton);

	// Menu buttons
	Button playButton2(screenWidth / 4 - 200, screenHeight / 2 - 100, "play", LEVEL);
	menuButtons.push_back(playButton2);
	Button escapeButton2(3 * screenWidth / 4 - 200, screenHeight / 2 - 100, "exit", ESCAPE);
	menuButtons.push_back(escapeButton2);
}

void Game::theLoop() {
	// The Loop
	while (loopType != ESCAPE) {
		switch (loopType) {
		case MENU: menu(); break;
		case LEVEL: level(); break;
		case PAUSE: pause(); break;
		}
	}
}

inline void Game::menu() {
	SDL_Event event;
	while (loopType == MENU) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_l && event.type == SDL_KEYDOWN)) { loopType = ESCAPE; std::cout << "based"; }
			if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : menuButtons) b.checkClick(&event);
		}
		for (auto&& b : menuButtons) b.onClick(&loopType);

		window->clear(); // Clearing the screen

		for (auto&& b : menuButtons) window->freeRender(&b);

		window->display(); // Display rendered stuff
	}
}

inline void Game::level() {
	// Level Generation

	SDL_Event event;
	while (loopType == LEVEL) {
		// Framerate handling
		int frameStart = SDL_GetTicks();

		// User input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) loopType = ESCAPE;
			if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) {
				for (auto&& p : players) p.stopMomentum();
				loopType = PAUSE;
				menu(); 
			}
			for (auto&& p : players) p.move(&event);
			window->handleWindow(&event);
		}

		// Handle User input
		for(auto&& p : players) p.handleMove(&cam.camera);

		// ###############################################################################################
		for (auto&& p : players) window->cam->move(&p);

		// Spriting
		for (auto&& p : players) p.changeSprite();

		//Rendering
		window->clear(); // Clearing the screen

		window->render(&map.tileMap);
		for (auto&& p : players) window->render(&p);

		for (auto&& p : players) {
			SDL_Rect colsrc = p.collider; // Collider
			colsrc.x -= (int)window->cam->x;
			colsrc.y -= (int)window->cam->y;
			SDL_RenderDrawRect(window->renderer, &colsrc);
		}
		
		window->display(); // Display rendered stuff

		// More framerate handling
		int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	}
}

void Game::pause() {
	SDL_Event event;
	while (loopType == PAUSE) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_l && event.type == SDL_KEYDOWN)) loopType = ESCAPE;
			if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : pauseButtons) b.checkClick(&event);
		}
		for (auto&& b : pauseButtons) b.onClick(&loopType);

		window->clear(); // Clearing the screen

		window->render(&map.tileMap);
		for (auto&& p : players) window->render(&p);
		for (auto&& b : pauseButtons) window->freeRender(&b);

		window->display(); // Display rendered stuff
	}
}

void Game::end() {
	window->destroy();
	SDL_Quit();
	TTF_Quit();
}