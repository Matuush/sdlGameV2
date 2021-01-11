#include "GameManager.h"

#include "Constants.h"

int main(int argc, char* args[]){
	Game game;

	game.theLoop();

	game.end();
	return 0;
}