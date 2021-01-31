#include "GameManager.h"
#include <windows.h>

char Game::loopType = MENU;

Game::Game() {
	UdpCom::start(); // Server
	UdpCom com(ip, 80);

	com.send("{ \"id\":\"da big chungus\" }");

	Map tempMap(window); // Map
	map = tempMap;

	// Players
	Player player(Vector2D(10, 10), &map.tileMap);
	players.push_back(player);
	/*Player player2(50.0f, 50.0f, &map.tileMap);
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
	Button playButton(Vector2D(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "play", [&]() { Game::loopType = LEVEL; });
	menuButtons.push_back(playButton);
	Button escapeButton(Vector2D(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "exit", [&]() { Game::loopType = ESCAPE; });
	menuButtons.push_back(escapeButton);
	Button fortniteButton(Vector2D(screenWidth - 700, 50), "fortnite", [&]() { Game::loopType = LEVEL; });
	menuButtons.push_back(fortniteButton);

	Button resumeButton(Vector2D(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "resume", [&]() { Game::loopType = LEVEL; });
	pauseButtons.push_back(resumeButton);
	Button menuButton(Vector2D(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "menu", [&]() { Game::loopType = MENU; });
	pauseButtons.push_back(menuButton);
	Button fortniteButtonp(Vector2D(screenWidth - 700, 50), "fortnite", [&]() { system("\"D:/Program Files/Games/Epic Games/Fortnite/FortniteGame/Binaries/Win64/FortniteClient-Win64-Shipping\""); });
	pauseButtons.push_back(fortniteButtonp);
	Button borderedButtonp(Vector2D(screenWidth / 4 - buttonWidth, screenHeight - buttonHeight - 50), "bordered", [&]() { RenderWindow::windowType = BORDERED; });
	pauseButtons.push_back(borderedButtonp);
	Button borderlessButtonp(Vector2D(screenWidth / 2 - buttonWidth, screenHeight - buttonHeight - 50), "borderless", [&]() { RenderWindow::windowType = BORDERLESS; });
	pauseButtons.push_back(borderlessButtonp);
	Button fullscreenButtonp(Vector2D(3 * screenWidth / 4 - buttonWidth, screenHeight - buttonHeight - 50), "fullscreen", [&]() { RenderWindow::windowType = FULLSCREEN; });
	pauseButtons.push_back(fullscreenButtonp);

	Entity prdel;
	std::vector<Entity> entities;
	entities.push_back(players[0]);
	entities.push_back(prdel);
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

void Game::menu() {
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

		window->renderBackground();

		for (auto&& b : menuButtons) window->freeRender(&b);

		window->display(); // Display rendered stuff
	}
}

void Game::level() {

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
		for(auto&& p : players) p.handleMove();

		// ###############################################################################################
		for (auto&& p : players) cam.move(&p);

		// Spriting
		for (auto&& p : players) p.changeSprite();

		//Rendering
		window->clear(); // Clearing the screen

		for (std::vector<Entity> row : map.tileMap)
			for (Entity tile : row) window->render(&tile);

		for (auto&& p : players) window->render(&p);

		for (auto&& p : players) {
			for (auto&& c : p.colliders) {
				SDL_Rect colsrc = { c.x, c.y, c.w, c.h }; // Collider
				colsrc.x -= (int)window->cam->x;
				colsrc.y -= (int)window->cam->y;
				SDL_RenderDrawRect(window->renderer, &colsrc);
			}
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

		for (std::vector<Entity> row : map.tileMap)
			for (Entity tile : row) window->render(&tile);
		for (auto&& p : players) window->render(&p);

		window->renderBackground();

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