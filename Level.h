#pragma once
#include "Map.h"
#include "Enemy.h"

struct Level {
	Map map = Map();
	Player player1 = Player(Vector2D(0, 0));
	Player player2 = Player(Vector2D(0, 128));
	Enemy enemy1 = Enemy(Vector2D(900, 900));

	Level() {}
	~Level() {
		Entity::entities.clear();
		Player::players.clear();
	}
};