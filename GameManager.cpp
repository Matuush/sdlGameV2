#include "GameManager.h"

Game::Game() {
	loopType = MENU;

	Map tempMap(window); // Map
	map = tempMap;

	Player player(10.0f, 10.0f, &map.tileMap);
	players.push_back(player); // Player
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
	SDL_Event menuEvent;
	Button escapeButton(100, 100, "exit");
	while (loopType == MENU) {
		while (SDL_PollEvent(&menuEvent)) {
			if (menuEvent.type == SDL_QUIT || menuEvent.key.keysym.sym == SDLK_l) loopType = ESCAPE;
			if (menuEvent.key.keysym.sym == SDLK_SPACE) loopType = LEVEL;
		}

		window->clear(); // Clearing the screen

		window->freeRender(&escapeButton);

		window->display(); // Display rendered stuff
	}
}

inline void Game::level() {
	// Level Generation

	SDL_Event gameEvent;
	while (loopType == LEVEL) {
		// Framerate handling
		int frameStart = SDL_GetTicks();

		// User input
		while (SDL_PollEvent(&gameEvent)) {
			if (gameEvent.type == SDL_QUIT) loopType = ESCAPE;
			if (gameEvent.key.keysym.sym == SDLK_ESCAPE) {
				for (auto&& p : players) p.stopMomentum();
				loopType = PAUSE;
				menu(); 
			}
			for (auto&& p : players) p.move(&gameEvent);
			window->handleWindow(&gameEvent);
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
	SDL_Event pauseEvent;
	Button escapeButton(100, 100, "bottom text");
	while (loopType == PAUSE) {
		while (SDL_PollEvent(&pauseEvent)) {
			if (pauseEvent.type == SDL_QUIT || pauseEvent.key.keysym.sym == SDLK_l) loopType = ESCAPE;
			if (pauseEvent.key.keysym.sym == SDLK_SPACE) loopType = LEVEL;
		}

		window->clear(); // Clearing the screen

		window->freeRender(&escapeButton);

		window->display(); // Display rendered stuff
	}
}

void Game::end() {
	window->destroy();
	SDL_Quit();
	TTF_Quit();
}