#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL.h>
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL_image.h>
#include <iostream>
#include "RenderWindow.h"

int main(int argc, char* args[]){
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "HEY... IMG_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;

	RenderWindow window("SDL MOMENT", 1280, 720);

	bool gameRunning = true;

	SDL_Event event;

	 while (gameRunning){
	 	while(SDL_PollEvent(&event)){
	 		if(event.type == SDL_QUIT)
	 			gameRunning = false;
	 	}
	 }

	window.cleanUp();
	SDL_Quit();

	return 0;
}