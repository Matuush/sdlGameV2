#pragma once
#include "data/Vector2D.hpp"
#include <vector>

enum COLLIDER_TYPE : unsigned char { CIRCLE, RECTANGLE };

struct Collider {
	Vector2D position, size;
	unsigned int radius;
	COLLIDER_TYPE type;
	Collider() = default;
	Collider(Collider* first) : position(first->position), size(first->size), radius(first->radius), type(first->type) {}
	Collider(Vector2D pos, Vector2D size) : type(RECTANGLE), position(pos), size(size), radius(0){	}
	Collider(int x, int y, int w, int h) : type(RECTANGLE), position({x, y}), size({w, h}), radius(0) {	}
	Collider(Vector2D pos, unsigned int size) : type(CIRCLE), position(pos), size({0, 0}), radius(size) {	}

	Collider operator*(const int value) {
		switch (type){
			case RECTANGLE: return Collider(position * value, size * value);
			case CIRCLE: return Collider(position * value, radius * value);
		}
		std::cout << "Unknown collider type\n";
		return Collider();
	}
	
	virtual bool collides(double x, double y) {
		switch (type) {
			case RECTANGLE: return(x >= position.x && y >= position.y && x <= position.x + size.x && y <= position.y + size.y);
			case CIRCLE: return Vector2D( abs(x - position.x), abs(y - position.y) ).getMagnitude() <= radius;
		}
		std::cout << "Unknown collider type\n";
		return false;
	}
	bool collides(Vector2D p) { return collides(p.x, p.y); }
	virtual bool collides(Collider* second) {
		switch (type) {
		case RECTANGLE:
			switch (second->type) {
			case RECTANGLE:
				return collides(second->position.x, second->position.y) ||
						collides(second->position.x + second->size.x, second->position.y) ||
						collides(second->position.x, second->position.y + second->size.y) ||
						collides(second->position.x + second->size.x, second->position.y + second->size.y) ||
						second->collides(position.x, position.y) ||
						second->collides(position.x + size.x, position.y) ||
						second->collides(position.x, position.y + size.y) ||
						second->collides(position.x + size.x, position.y + size.y);
			case CIRCLE:
				return second->collides(this);
			}
			std::cout << "Unknown collider type\n";
			return false;
			break;
		case CIRCLE:
			switch (second->type) {
			case RECTANGLE:
				 return collides(second->position) ||
					collides(second->position + Vector2D((int)second->size.x, 0)) ||
					collides(second->position + Vector2D(0, (int)second->size.y)) ||
					collides(second->position + second->size) || 
					second->collides(position.x + radius, position.y) ||
					second->collides(position.x - radius, position.y) ||
					second->collides(position.x, position.y + radius) ||
					second->collides(position.x, position.y - radius);
			case CIRCLE:
				return abs((position - second->position).getMagnitude()) <= radius + second->radius;
			}
			std::cout << "Unknown collider type\n";
			return false;
			break;
		}
		std::cout << "Unknown collider type\n";
		return false;
		
	}
};

struct MultiCollider {
	std::vector<Collider*> colliders;
	MultiCollider() = default;
	MultiCollider(std::vector<Collider*> p_colliders) : colliders(p_colliders) {}

	void add(Collider* col){
		colliders.push_back(col);
	}
	void move(Vector2D vel) {
		for (Collider* c : colliders) c->position += vel;
	}
	bool collides(double x, double y) {
		for (Collider* c : colliders) if (c->collides(x, y)) return true;
		return false;
	}
	bool collides(Collider* second) {
		for (Collider* c : colliders) if (c->collides(second)) return true;
		return false;
	}
	bool collides(MultiCollider* second) {
		for (Collider* c : colliders)
			for (Collider* d : second->colliders)
				if (c->collides(d)) return true;
		return false;
	}
};