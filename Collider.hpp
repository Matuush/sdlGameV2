#pragma once
#include "Vector2D.hpp"
#include <vector>

enum COLLIDER_TYPE : unsigned char { CIRCLE, RECTANGLE };

std::vector<Vector2D> sort(std::vector<Vector2D> prdle) {
	std::vector<Vector2D> result;
	result.push_back(prdle[0]);
	prdle.erase(prdle.begin());
	for (auto v : prdle) {
		if (v.getMagnitude() > result[result.size()].getMagnitude()) result.push_back(v);
		else {
			unsigned int aah = result.size() - 1;
			for (; aah >= 0; aah--) {
				if (result[aah] < v) continue;
				result.insert(result.begin() + aah, v);
			}
		}
	}
	return result;
}

struct Collider {
	Vector2D position, size;
	unsigned int radius;
	COLLIDER_TYPE type;
	Collider() = default;
	Collider(Vector2D pos, Vector2D size) : type(RECTANGLE), position(pos), size(size), radius(0){	}
	Collider(const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h) : type(RECTANGLE), position({x, y}), size({w, h}), radius(0) {	}
	Collider(Vector2D pos, unsigned int size) : type(CIRCLE), position(pos), size({0, 0}), radius(radius) {	}
	Collider operator*(const int value) { 
		switch (type){
		case RECTANGLE:
			return Collider(position * value, size * value);
		case CIRCLE:
			return Collider(position * value, radius * value);
		}
		std::cout << "Unknown collider type\n";
		return Collider();
	}
	virtual bool collides(double x, double y) {
		switch (type) {
		case RECTANGLE:
			return(x >= position.x && y >= position.y && x <= position.x + size.x && y <= position.y + size.y);
		case CIRCLE:
			return Vector2D{ abs(x - position.x), abs(y - position.y) }.getMagnitude() <= radius ? true : false;
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
				return(collides(second->position.x, second->position.y) ||
					collides(second->position.x + second->size.x, second->position.y) ||
					collides(second->position.x, second->position.y + second->size.y) ||
					collides(second->position.x + second->size.x, second->position.y + second->size.y)) ||
					(second->collides(position.x, position.y) ||
						second->collides(position.x + size.x, position.y) ||
						second->collides(position.x, position.y + size.y) ||
						second->collides(position.x + size.x, position.y + size.y));
			case CIRCLE:
				if (collides(second->position)) return true;
				std::vector<Vector2D> a = {
					position - second->position,
					position + size - second->position,
					Vector2D(position.x, position.y + size.y) - second->position,
					Vector2D(position.x + size.x, position.y) - second->position
				};
				a = sort(a);
				return false;
			}
			std::cout << "Unknown collider type\n";
			return false;
			break;
		case CIRCLE:
			switch (second->type) {
			case RECTANGLE:
				return second->collides(this);
			case CIRCLE:
				return abs((position - second->position).getMagnitude()) <= radius + second->radius ? true : false;
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
	~MultiCollider() {
		//for (Collider* c : colliders) delete c;
		colliders.clear();
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