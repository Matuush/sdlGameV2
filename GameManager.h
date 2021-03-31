#pragma once
#include "SDL/SDL_main.h"
#include "RenderWindow.h"
#include "Level.h"
#include "MenuPage.h"

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
			case MENU: menu(startMenu); break;
			case LEVEL: level(); break;
			case PAUSE: menu(pause); break;
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

	Page levelSelector = Page(LEVEL_SELECTOR, { 
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2), "level 1", []() { loopType = LEVEL; })
	});
	Page startMenu = Page(MENU, {
		Button(Vector2D(SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2), "levels", [&]() { menu(levelSelector); }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2), "exit", []() { loopType = ESCAPE; }),
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2 + 300), "settings", [&]() { LOOP_TYPE tempLoopT = loopType; menu(settings); if (loopType != LEVEL) loopType = tempLoopT;})
	});
	Page pause = Page(PAUSE, {
		Button(Vector2D(SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2), "resume", []() { Game::loopType = LEVEL; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2), "menu", []() { Game::loopType = MENU; }),
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y / 2 - BUTTON_SIZE.y / 2 + 300), "settings", [&]() { LOOP_TYPE tempLoopT = Game::loopType; menu(settings); if (Game::loopType != LEVEL) Game::loopType = tempLoopT;})
	});
	Page settings = Page(SETTINGS, {
		Button(Vector2D(SCREEN_SIZE.x / 4 - BUTTON_SIZE.x * 3 / 4, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "bordered", []() { RenderWindow::windowType = BORDERED; }),
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "borderless", []() { RenderWindow::windowType = BORDERLESS; }),
		Button(Vector2D(3 * SCREEN_SIZE.x / 4 - BUTTON_SIZE.x / 4, SCREEN_SIZE.y - BUTTON_SIZE.y - 50), "fullscreen", []() { RenderWindow::windowType = FULLSCREEN; }),
		Button(Vector2D(SCREEN_SIZE.x / 2 - BUTTON_SIZE.x / 2, 100.0), "back", []() { loopType = ESCAPE; })
	});

	inline void menu(Page page) {
		loopType = page.loopType;
		SDL_Event event;
		while (loopType == page.loopType) {
			int frameStart = SDL_GetTicks();
			if (loopType == PAUSE) RenderWindow::paused = true;

			// User input
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) loopType = ESCAPE;
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && window->paused) loopType = LEVEL;
				for (auto& b : page.buttons) b.checkClick(&event);
			}

			// Updates
			window->handleWindow();
			for (auto& b : page.buttons) b.onClick();

			// Rendering
			window->clear();
				if(window->paused) for (Entity* e : Entity::entities) window->render(e);
				window->renderBackground();
				for (auto& b : page.buttons) window->freeRender(&b);
			window->display();

			{ int frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frameTime); }
		}
		window->paused = false;
	}
	inline void level() {
		window->cam->refresh();
		Level level(&window->cam->position); SDL_Event event;
		while (loopType == LEVEL) {
			int frameStart = SDL_GetTicks();

			// User input
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) loopType = ESCAPE;
				else if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) {
					for (auto& p : Player::players) p->keyState.zeroify();
					loopType = PAUSE;
					menu(pause);
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
};