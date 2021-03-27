#include "GameManager.h"
bool RenderWindow::paused = 0;
char RenderWindow::windowType = 1;
bool RenderWindow::renderColliders = 0;
char Game::loopType = MENU;
std::vector<Player*> Player::players;
std::vector<Entity*>Entity::entities;
int main(int argc, char* args[]){
	Game game;

	game.theLoop();

	game.end();
	return 0;
}