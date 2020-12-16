#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL.h>
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL_image.h>
#include <iostream>
#include <vector>
#include <string>

#include "RenderWindow.h"
#include "Entity.h"
#include "Map.h"

int main(int argc, char* args[]){
	//INIT
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY... SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "HEY... IMG_Init HAS FAILED. ERROR: " << SDL_GetError() << std::endl;

	const int mapSizeWidth = 14*3;
	const int mapSizeHeight = 7*3;
	std::string seed = "B";

	RenderWindow window("SDL MOMENT", mapSizeWidth/3*128, mapSizeHeight/3*128);

	// Generace mapy
	Map map1(mapSizeWidth, mapSizeHeight);
	map1.generateMap(seed);
	map1.setWindow(&window);
	map1.setTextures();
	map1.map[6][5] = 1;
	map1.map[5][4] = 3;

	// Game Loop
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
			for (int height = 0; height < map1.map[width].size(); height++) map1.renderTile(width, height);
		}

		window.display();
	 }

	 // Konec
	window.cleanUp();
	SDL_Quit();
	return 0;
}