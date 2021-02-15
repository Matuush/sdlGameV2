#include "Entity.h"

std::vector<Entity*>Entity::entities;

Entity::Entity(Vector2D p_position, Texture p_texture) : position(p_position), textureID(p_texture.id) {
	init();
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_texture.width;
	currentFrame.h = p_texture.height;
	colliders.push_back(RectangleCollider(position.x, position.y, tileSize, tileSize));
	Entity::entities.push_back(this);
}

Entity::Entity(Vector2D p_position, RectangleCollider p_collider, Texture p_texture) : position(p_position), textureID(p_texture.id) {
	init();
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_texture.width;
	currentFrame.h = p_texture.height;
	colliders.push_back(RectangleCollider(position.x, position.y, tileSize, tileSize));
	Entity::entities.push_back(this);
}

Entity::Entity(Vector2D p_position) : position(p_position), textureID(nothingTexture.id) {
	init();
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = nothingTexture.width;
	currentFrame.h = nothingTexture.height;

	Entity::entities.push_back(this);
}

void Entity::init() {
	acceleration = Vector2D(0, 0);
	velocity = Vector2D(0, 0);
	colliders;
}

void Entity::updatePosition() {
	Vector2D pp(position.x, position.y);

	if (solid) {
		bool xCollides = false;
		for (RectangleCollider& c : colliders) {
			c.x += velocity.x;
			for (Entity* e : Entity::entities) {
				if (!e->solid || e == this) continue;
				for (RectangleCollider cc : e->colliders)
					if (c.collides(&cc)) xCollides = 1;
				if (xCollides) break;
			} // o kurva
			c.x -= velocity.x;
			if (xCollides) break;
		}
		if (!xCollides) position.x += velocity.x;

		bool yCollides = false;
		for (RectangleCollider& c : colliders) {
			c.y += velocity.y;
			for (Entity* e : Entity::entities) {
				if (!e->solid || e == this) continue;
				for (RectangleCollider cc : e->colliders)
					if (c.collides(&cc)) yCollides = 1;
				if (yCollides) break;
			}
			c.y -= velocity.y;
			if (xCollides) break;
		}
		if (!yCollides) {
			position.y += velocity.y;
		}
	}
	else position = position + velocity;

	Vector2D dif = position - pp;
	for (RectangleCollider& c : colliders) {
		c.x += dif.x;
		c.y += dif.y;
	}
}

void Entity::update() {
	velocity = (velocity + acceleration);
	velocity.limit(terminalVelocity);

	updatePosition();
}

void Entity::updateAll() {
	for (auto& e : Entity::entities)
		e->update();
}

void Entity::input(SDL_Event* event) {

}

void Entity::inputAll(SDL_Event* event) {
	for (auto& e : Entity::entities)
		e->input(event);
}

bool Entity::collides(Entity* second) {
	for (RectangleCollider c : colliders)
		for (RectangleCollider cc : second->colliders)
			if (c.collides(&cc)) return true;
	return false;
}