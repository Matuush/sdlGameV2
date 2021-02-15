#include "GameManager.h"
#include <windows.h>

char Game::loopType = MENU;

Game::Game() {
	// Server
	UdpCom::start();
	UdpCom com(ip, 80);
	com.send("{ \"id\":\"da big chungus\" }");

	// Menu buttons
	menuButtons.push_back(Button(Vector2D(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "play", [&]() { Game::loopType = LEVEL; }));
	menuButtons.push_back(Button(Vector2D(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "exit", [&]() { Game::loopType = ESCAPE; }));
	menuButtons.push_back(Button(Vector2D(screenWidth - 700, 50), "fortnite", [&]() { Game::loopType = LEVEL; }));

	// Pause buttons
	pauseButtons.push_back(Button(Vector2D(screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "resume", [&]() { Game::loopType = LEVEL; }));
	pauseButtons.push_back(Button(Vector2D(3 * screenWidth / 4 - tileSize * 2, screenHeight / 2 - tileSize), "menu", [&]() { Game::loopType = MENU; }));
	pauseButtons.push_back(Button(Vector2D(screenWidth - 700, 50), "fortnite", [&]() { system("\"D:/Program Files/Games/Epic Games/Fortnite/FortniteGame/Binaries/Win64/FortniteClient-Win64-Shipping\""); }));
	pauseButtons.push_back(Button(Vector2D(screenWidth / 4 - buttonWidth * 3 / 4, screenHeight - buttonHeight - 50), "bordered", [&]() { RenderWindow::windowType = BORDERED; }));
	pauseButtons.push_back(Button(Vector2D(screenWidth / 2 - buttonWidth / 2, screenHeight - buttonHeight - 50), "borderless", [&]() { RenderWindow::windowType = BORDERLESS; }));
	pauseButtons.push_back(Button(Vector2D(3 * screenWidth / 4 - buttonWidth / 4, screenHeight - buttonHeight - 50), "fullscreen", [&]() { RenderWindow::windowType = FULLSCREEN; }));
}

void Game::theLoop() {
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
		int frameStart = SDL_GetTicks();

		// User input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { loopType = ESCAPE; }
			else if (event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : menuButtons) b.checkClick(&event);
		}

		//Updates
		window->handleWindow();
		for (auto&& b : menuButtons) b.onClick();

		// Rendering
		window->clear();
			window->renderBackground();
			for (auto&& b : menuButtons) window->freeRender(&b);
		window->display();

		int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	}
}

void Game::level() {
	Entity::entities.push_back(&cam);
	Level level;
	SDL_Event event;
	while (loopType == LEVEL) {
		int frameStart = SDL_GetTicks();

		// User input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) loopType = ESCAPE;
			else if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) {
				for (auto&& p : Player::players) p->keyState.zeroify();
				loopType = PAUSE;
				pause();
				if (loopType != LEVEL)
					return;
			}
			Entity::inputAll(&event);
		}

		// Updates
		window->handleWindow();
		Entity::updateAll();

		//Rendering
		window->clear();
			for (Entity* e : Entity::entities) window->render(e);
			window->displayStats(Player::players[0]);
		window->display();

		int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	}
}

void Game::pause() {
	window->paused = 1;
	SDL_Event event;
	while (loopType == PAUSE) {
		int frameStart = SDL_GetTicks();

		// User input
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) loopType = ESCAPE;
			else if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) loopType = LEVEL;
			for (auto&& b : pauseButtons) b.checkClick(&event);
		}

		//Updates
		window->handleWindow();
		for (auto&& b : pauseButtons) b.onClick();

		// Rendering
		window->clear();
			for (Entity* e : Entity::entities) window->render(e);
			window->renderBackground();
			for (auto&& b : pauseButtons) window->freeRender(&b);
		window->display();

		int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	}
	window->paused = 0;
}

void Game::end() {
	window->destroy();
	SDL_Quit();
	TTF_Quit();
}