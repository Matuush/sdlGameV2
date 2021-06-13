#pragma once
#include "SDL2/SDL.h"
#include "data/Constants.hpp"
#include <iostream>

class Entity;

template <class IT, class T>
IT findIter(IT first, IT last, T value){
    for (; first != last; ++first)
        if (*first == value) return first;
    return last;
}

class Entity {
public:
	static std::vector<Entity*> entities;

	// Visual
	SDL_Rect currentFrame = {0, 0, RAW_TILE, RAW_TILE};
	Texture texture = NOTHING_TEXTURE;
	bool lastRight = true, display = true;

	// Material
	Vector2D position, velocity;
	MultiCollider colliders;
	bool solid = 0;

	Entity() { init(); }
	Entity(Vector2D p_position, Texture p_texture = NOTHING_TEXTURE) : position(p_position), texture(p_texture) {
		init();
		currentFrame = { 0, 0, texture.width, texture.height };
		if (texture.id != ENEMY_TEXTURE.id && texture.id != PLAYER_TEXTURE.id && texture.id != BULLET_TEXTURE.id) colliders.add(new Collider(position, {TILE_SIZE, TILE_SIZE}));
		Entity::entities.push_back(this);
	}
	Entity(Vector2D p_position, std::vector<Collider*> p_colliders, Texture p_texture) : position(p_position), texture(p_texture) {
		init();
		colliders.colliders = p_colliders;
		currentFrame = { 0, 0, texture.width, texture.height };
		Entity::entities.push_back(this);
	}
	~Entity() {
		for(Collider* col : colliders.colliders) delete col;
		Entity::entities.erase(findIter(Entity::entities.begin(), Entity::entities.end(), this));
	}
	bool collides(Entity* second) {
		return colliders.collides(&second->colliders);
	}
	Vector2D getCenter(){
		return(Vector2D(
			position.x + texture.width * SCALE / 2,
			position.y + texture.height * SCALE / 2	
		));
	}

protected:
	Vector2D acceleration;
	double terminalVelocity = DEFAULT_TERMINAL_VELOCITY;

	inline void init() {
		acceleration = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		colliders;
	}
	inline bool collisionOnMovement(Vector2D vel) {
		bool axisCollides = false;
		colliders.move(vel);
		for (Entity* e : Entity::entities) {
			if (!e->solid || e == this) continue;
			else if (colliders.collides(&e->colliders)) {
				axisCollides = true;
				break;
			}
		}
		colliders.move(Vector2D{0, 0}-vel);
		return axisCollides;
	}

	inline void updatePosCareless() {
		velocity.limit(terminalVelocity);

		if (solid) {
			if (!collisionOnMovement({ velocity.x, 0.0 })) move({velocity.x, 0.0});
			if (!collisionOnMovement({ 0.0, velocity.y })) move({0.0, velocity.y});
		}
		else move(velocity);

		velocity *= 1 - FRICTION;
		if (velocity.getMagnitude() < 0.5) velocity = 0;
	}

	inline void move(Vector2D vel) {
		position += vel;
		colliders.move(vel);
	}
};

class Creature : public Entity{
public:
	double movementAcceleration = PLAYER_VELOCITY;
	double health, damage, maxHealth;
	unsigned int hurtTimer = 0;
	static std::vector<Creature*> creatures;
	Creature() = default;
	Creature(Vector2D p_position, Texture p_texture, double p_health, double p_damage) : Entity(p_position, p_texture) {
		solid = true;
		health = p_health, damage = p_damage;
		maxHealth = health;
		creatures.push_back(this);
	}
	~Creature(){
		Creature::creatures.erase(findIter(Creature::creatures.begin(), Creature::creatures.end(), this));
	}
	static void inputAll(SDL_Event* event) {
		for (Creature* e : Creature::creatures) e->input(event);
	}
	static void updateAll() {
		for (Creature* e : Creature::creatures) e->update();
	}
	void oof(Creature* creature){
		health -= creature->damage;
		hurtTimer = 255;
	}
	void recoil(Vector2D shotPos, double how = 3) {
		Vector2D tAcceleration = getCenter() - shotPos;
		tAcceleration.limit(movementAcceleration * how);
		velocity += tAcceleration;
	}

private:
	virtual void input(SDL_Event* event) {}
	virtual void update() {}
};