#pragma once
#include "Vector2D.hpp"
struct KeyState {
	bool w = 0, s = 0, a = 0, d = 0;
	Vector2D lcPos = DEFAULT_BULLET_POSITION;
	KeyState() = default;
	void zeroify() { w = 0, s = 0, a = 0, d = 0; }
	void update(SDL_Event* event){
		switch (event->type) {
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym) {
					case SDLK_w: w = 1; break;
					case SDLK_a: a = 1; break;
					case SDLK_s: s = 1; break;
					case SDLK_d: d = 1; break;
				}
				break;
			case SDL_KEYUP:
				switch (event->key.keysym.sym) {
					case SDLK_w: w = 0; break;
					case SDLK_a: a = 0; break;
					case SDLK_s: s = 0; break;
					case SDLK_d: d = 0; break;
				}
			break;
		}
	}
};