#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"

#include "Constants.h"

int main(int argc, char* args[]){

	// Generation
	Camera cam;
	RenderWindow window(&cam);
	Map map1(&window);
	map1.tileMap[5][5].changeTextureID(WATER);
	map1.tileMap[4][4].changeTextureID(WATER);
	Player player(10.0f, 10.0f, &map1.tileMap);

	SDL_SetRenderDrawColor(window.renderer, 255, 0, 0, 0);

	// Game Loop
	bool gameRunning = true;
	SDL_Event event;
	 while (gameRunning){
		 // Framerate handling
		 int frameStart = SDL_GetTicks();

		 // User input
	 	while(SDL_PollEvent(&event)){
	 		if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) gameRunning = false;
			player.move(&event);
			window.handleWindow(&event);
	 	}
		player.handleMove();
		cam.move(&player);

		// Spriting
		player.changeSprite();

		window.clear();
		//Rendering
		window.render(&map1.tileMap);
		window.render(&player, player.lastRight);

		SDL_Rect colsrc = player.collider;
		colsrc.x -= (int)cam.x;
		colsrc.y -= (int)cam.y;
		SDL_RenderDrawRect(window.renderer, &colsrc);

		window.display();

		// More framerate handling
		int frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	 }

	 // End
	window.destroy();
	SDL_Quit();
	return 0;
}