#pragma once
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL.h>
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL_image.h>

class RenderWindow {
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};