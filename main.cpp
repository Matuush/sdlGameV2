#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL.h>
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Map.h"

int main(int argc, char* args[]){
	//INIT
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "HEY... IMG_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;

	const int mapSizeWidth = 14;
	const int mapSizeHeight = 7;

	RenderWindow window("SDL MOMENT", mapSizeWidth*128, mapSizeHeight*128);
	Map map1(mapSizeWidth, mapSizeHeight);
	map1.map[6][5] = 1;

	bool gameRunning = true;
	SDL_Event event;

	 while (gameRunning){
	 	while(SDL_PollEvent(&event)){
	 		if(event.type == SDL_QUIT)
	 			gameRunning = false;
	 	}

		window.clear();

		//Renderování
		for (int width = 0; width < map1.map.size(); width++) {
			for (int height = 0; height < map1.map[width].size(); height++) map1.render(width, height);
		}

		window.display();
	 }


	window.cleanUp();
	SDL_Quit();
	return 0;
}