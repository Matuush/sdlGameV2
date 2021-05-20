#pragma once
#include "data/Map.hpp"
#include "Enemy.hpp"

struct Level {
	Enemy enemy1 = Enemy(Vector2D(900, 900));
	Map map = Map();
	Player player1 = Player(Vector2D(0, 0));

	Level() {}
	~Level() {
		for(Entity* e : Entity::entities) delete e;
		Player::players.clear();
	}
};