#include "GameManager.h"

char Game::loopType = MENU;

void temp1() { Game::loopType = LEVEL; }

void temp2() { Game::loopType = ESCAPE; }

void temp3() { Game::loopType = MENU; }

void temp4() { RenderWindow::bordered = !RenderWindow::bordered; };

Game::Game() {
	UdpCom::start(); // Server
	UdpCom com(ip, 80);

	com.send("{ \"id\":\"da big chungus\" }");

	Map tempMap(window); // Map
	map = tempMap;

	// Players
	Player player(10.0f, 10.0f, &map.tileMap);
	players.push_back(player);/*
	Player player2(50.0f, 50.0f, &map.tileMap);
	players.push_back(player2);
	Player player3(90.0f, 90.0f, &map.tileMap);
	players.push_back(player3);
	Player player4(130.0f, 130.0f, &map.tileMap);
	players.push_back(player4);
	Player player5(170.0f, 170.0f, &map.tileMap);
	players.push_back(player5);
	Player player6(210.0f, 210.0f, &map.tileMap);
	players.push_back(player6);*/

	// Buttons
	Button playButton(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize, "play", temp1);
	menuButtons.push_back(playButton);
	Button escapeButton(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize, "exit", temp2);
	menuButtons.push_back(escapeButton);
	Button borderedButton(screenWidth - 700, 50, "fortnite", temp4);
	menuButtons.push_back(borderedButton);

	Button resumeButton(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize, "resume", temp1);
	pauseButtons.push_back(resumeButton);
	Button menuButton(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize, "menu", temp3);
	pauseButtons.push_back(menuButton);
	Button borderedButtonp(screenWidth - 700, 50, "fortnite", temp4);
	pauseButtons.push_back(borderedButtonp);

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
			if (event.type == SDL_QUIT) { loopType = ESCAPE; std::cout << "based"; }
			if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : menuButtons) b.checkClick(&event);
		}
		window->handleWindow();
		for (auto&& b : menuButtons) b.onClick();

		window->clear(); // Clearing the screen

		window->renderBackground(background);

		for (auto&& b : menuButtons) window->freeRender(&b);

		window->display(); // Display rendered stuff
	}
}

inline void Game::level() {

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
		}
		window->handleWindow();

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
	window->paused = 1;
	SDL_Event event;
	while (loopType == PAUSE) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_l && event.type == SDL_KEYDOWN)) loopType = ESCAPE;
			if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : pauseButtons) b.checkClick(&event);
		}
		window->handleWindow();
		for (auto&& b : pauseButtons) b.onClick();

		window->clear(); // Clearing the screen

		window->render(&map.tileMap);
		for (auto&& p : players) window->render(&p);

		window->renderBackground(background);

		for (auto&& b : pauseButtons) window->freeRender(&b);

		window->display(); // Display rendered stuff
	}

	window->paused = 0;
}

void Game::end() {
	window->destroy();
	SDL_Quit();
	TTF_Quit();
}