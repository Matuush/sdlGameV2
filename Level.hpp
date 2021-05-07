#pragma once
#include "data/Map.hpp"
#include "Enemy.hpp"

struct Level {
	Map map = Map();
	Player player1 = Player(Vector2D(0, 0));
	Enemy enemy1 = Enemy(Vector2D(900, 900));

	Level() {}
	~Level() {
		Entity::entities.clear();
		//for(Entity* e : Entity::entities) delete e;
	}
};