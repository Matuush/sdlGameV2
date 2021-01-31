#include "Entity.h"

std::vector<Entity*>Entity::entities;
Entity::Entity() : position(Vector2D(100, 100)), textureID(nothingTexture.id) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = rawTile;
	currentFrame.h = rawTile;
	colliders.push_back(RectangleCollider(position.x, position.y, tileSize, tileSize));
	Entity::entities.push_back(this);
}

Entity::Entity(Vector2D p_position, Texture p_texture) : position(p_position), textureID(p_texture.id) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_texture.width;
	currentFrame.h = p_texture.height;
	colliders.push_back(RectangleCollider(position.x, position.y, tileSize, tileSize));
	Entity::entities.push_back(this);
}

Entity::Entity(Vector2D p_position, RectangleCollider p_collider, Texture p_texture) : position(p_position), textureID(p_texture.id) {
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_texture.width;
	currentFrame.h = p_texture.height;
	colliders.push_back(RectangleCollider(position.x, position.y, tileSize, tileSize));
	Entity::entities.push_back(this);
}

void Entity::update() {

}

void Entity::updateAll() {
	for (Entity* e : Entity::entities)
		e->update();
}

bool Entity::collides(Entity* second) {
	for (RectangleCollider c : colliders)
		for (RectangleCollider cc : second->colliders)
			if (c.collides(&cc)) return true;
	return false;
}