#include "GameManager.h"

int main(int argc, char* args[]){
	Game game;
	std::cout << Entity::entities.size() << std::endl;
	for (auto e : Entity::entities) std::cout << e->colliders.size() << std::endl;
	game.theLoop();

	game.end();
	return 0;
}