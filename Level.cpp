#include "Level.h"

Level::Level() {
	borderWall.colliders.push_back(RectangleCollider(0, mapSizeHeight, mapSizeWidth, 100));
	borderWall.colliders.push_back(RectangleCollider(mapSizeWidth, 0, 100, mapSizeHeight));
	borderWall.colliders.push_back(RectangleCollider(0, -100, mapSizeWidth, 100));
	borderWall.colliders.push_back(RectangleCollider(-100, 0, 100, mapSizeHeight));
	borderWall.solid = true;
}

Level::~Level(){
	Entity::entities.clear();
	Player::players.clear();
}