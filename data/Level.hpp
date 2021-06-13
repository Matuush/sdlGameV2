#pragma once
#include "../Map.hpp"
#include "../Enemy.hpp"

struct Level {
	Map* map = new Map();
	Player* player1 = new Player(Vector2D(0, 0));
	Enemy* enemy1 = new Enemy(Vector2D(900, 900));

	Level() {}
	~Level() {
		delete map;
		delete player1;
		delete enemy1;
		for(Projectile* e : Projectile::projectiles) delete e;
	}
};