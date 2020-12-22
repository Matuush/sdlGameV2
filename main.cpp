#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL.h>
#include <C:\Programy\C++\SDL Projekty\SDL2-2.0.12\include\SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "Constants.h"

const bool jiriSmrdi = 1;

int main(int argc, char* args[]){

	// Display generation
	Camera cam;
	RenderWindow window("SDL MOMENT", &cam);

	// Map generation
	Map map1(&window);
	map1.generateMap(seed);

	// Player generation
	Player player(10.0f, 10.0f, window.loadTexture("textures/player.png"));

	// Game Loop
	bool gameRunning = true;
	SDL_Event event;
	 while (gameRunning){
		 // Framerate handling
		 int frameStart, frameTime;
		 frameStart = SDL_GetTicks();

		 // Event handling
	 	while(SDL_PollEvent(&event)){
	 		if(event.type == SDL_QUIT) gameRunning = false;
			player.move(&event);
	 	}
		player.handleMove();
		cam.move(&player);

		// Spriting
		if (((player.left == 0 && player.right == 0) || (player.left == 1 && player.right == 1)) &&  ((player.up == 0 && player.down == 0) || (player.up == 1 && player.down == 1))) {
			player.getCurrentFrame()->y = 64;
			player.getCurrentFrame()->x = (SDL_GetTicks() / 100 % 4 + 1) * 64;
		}
		else {
			int tick = (SDL_GetTicks() / (500 / (int)speed)) % 6;
			if (tick != 5) {
				player.getCurrentFrame()->y = 0;
				player.getCurrentFrame()->x = (tick) * 64;
			}
			else {
				player.getCurrentFrame()->y = 64;
				player.getCurrentFrame()->x = 0;
			}
		}

		window.clear();
		//Rendering
		for (int width = 0; width < mapTileCountWidth; width++) {
			for (int height = 0; height < mapTileCountHeight; height++) window.render(&map1.tileMap[width][height]);
		}
		if (player.lastRight == 1) window.render(&player);
		if (player.lastRight == 0) window.renderFlip(&player);
		window.display();

		// More framerate handling
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	 }

	 // End
	window.destroy();
	SDL_Quit();
	return 0;
}