#pragma once
#include "SDL/SDL_main.h"
#include "RenderWindow.h"
#include "Level.h"
bool com = 0;
#if com 
#include "UdpCom.h" 
#endif

class Game {
public:
	static LOOP_TYPE loopType;

	Game() {
#if com
		UdpCom::start();
		UdpCom com(ip, 80);
		com.send("{ \"id\":\"da big chungus\" }");
#endif
	}

	void theLoop() {
		while (loopType != ESCAPE) {
			switch (loopType) {
			case MENU: menu(menuButtons); break;
			case LEVEL: level(); break;
			case PAUSE: pause(); break;
			}
		}
	}

	void end() {
		window->destroy();
		SDL_Quit();
		TTF_Quit();
	}

private:
	const char* ip = "10.49.0.6";
	int port = 80;

	RenderWindow* window = new RenderWindow();

	Button levelButtons[5] = {

	};
	Button menuButtons[3] = {
		Button(Vector2D(SCREEN_SIZE.x / 4 - TILE_SIZE * 2, SCREEN_SIZE.y / 2 - TILE_SIZE), "play", []() { Game::loopType = LEVEL; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - TILE_SIZE * 2, SCREEN_SIZE.y / 2 - TILE_SIZE), "exit", []() { Game::loopType = ESCAPE; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - TILE_SIZE * 2, SCREEN_SIZE.y / 2 - TILE_SIZE - TILE_SIZE / 4 - BUTTON_SIZE.y), "levels", [&]() { Game::loopType = LEVEL_SELECTOR;  levelSelector(); })
	};
	Button pauseButtons[5] = {
		Button(Vector2D(SCREEN_SIZE.x / 4 - TILE_SIZE * 2, SCREEN_SIZE.y / 2 - TILE_SIZE), "resume", []() { Game::loopType = LEVEL; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - TILE_SIZE * 2, SCREEN_SIZE.y / 2 - TILE_SIZE), "menu", []() { Game::loopType = MENU; }),
		Button(Vector2D(SCREEN_SIZE.x / 4 - BUTTON_SIZE.x * 3 / 4, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "bordered", []() { RenderWindow::windowType = BORDERED; }),
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "borderless", []() { RenderWindow::windowType = BORDERLESS; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 4, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "fullscreen", []() { RenderWindow::windowType = FULLSCREEN; })
	};

	inline void menu(Button arr[]) {
		SDL_Event event;
		while (loopType == MENU) {
			int frameStart = SDL_GetTicks();

			// User input
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) loopType = ESCAPE;
				for (auto b : arr) b.checkClick(&event);
			}

			// Updates
			window->handleWindow();
			for (auto&& b : arr) b.onClick();

			// Rendering
			window->clear();
			window->renderBackground();
			for (auto&& b : arr) window->freeRender(&b);
			window->display();

			{ int frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime); }
		}
	}
	inline void level() {
		window->cam->refresh();
		Level level; SDL_Event event;
		while (loopType == LEVEL) {
			int frameStart = SDL_GetTicks();

			// User input
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) loopType = ESCAPE;
				else if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) {
					for (auto&& p : Player::players) p->keyState.zeroify();
					loopType = PAUSE;
					pause();
					if (loopType != LEVEL) return;
				}
				Entity::inputAll(&event);
			}

			// Updates
			window->handleWindow();
			Entity::updateAll();

			// Rendering
			window->clear();
				for (Entity* e : Entity::entities) window->render(e);
				window->displayStats(Player::players);
			window->display();

			{ int frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime); }
		}
	}
	inline void pause() {
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

			// Updates
			window->handleWindow();
			for (auto&& b : pauseButtons) b.onClick();

			// Rendering
			window->clear();
				for (Entity* e : Entity::entities) window->render(e);
				window->renderBackground();
				for (auto&& b : pauseButtons) window->freeRender(&b);
			window->display();

			{ int frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime); }
		}
		window->paused = 0;
	}
};