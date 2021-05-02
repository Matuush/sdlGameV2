#include "GameManager.hpp"
bool RenderWindow::paused = 0, RenderWindow::renderColliders = 1;
WINDOW_TYPE RenderWindow::windowType = BORDERED;
LOOP_TYPE Game::loopType = MENU;
std::vector<Player*> Player::players;
std::vector<Entity*> Entity::entities;
unsigned char Texture::freeID = 0;

int main(int argc, char* args[]){
	Game game;
	game.theLoop();
	game.end();
	return 0;
}