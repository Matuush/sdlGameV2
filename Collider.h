#pragma once
#include "Vector2D.h"
#include <vector>

struct RectangleCollider;
struct CircleCollider;
struct MultiCollider;

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
	Vector2D position;
	virtual bool collides(double x, double y) {};
	virtual bool collides(Vector2D p) {};
	virtual bool collides(RectangleCollider* second) {};
	virtual bool collides(CircleCollider* second) {};
	virtual bool collides(MultiCollider* second) {};
	bool collides(Collider* second) { return false; }
};

struct CircleCollider : public Collider {
	unsigned int size;
	CircleCollider() = default;
	CircleCollider(Vector2D p_position, unsigned int p_size) : size(p_size) { position = p_position; }
	bool collides(Vector2D p) override { return collides(p.x, p.y); }
	bool collides(double x, double y) override { return Vector2D{ abs(x - position.x), abs(y - position.y) }.getMagnitude() <= size ? true : false; }
	bool collides(RectangleCollider* second) override { 
		if (second->collides(position)) return true;
		std::vector<Vector2D> a = {
			second->position - position,
			second->position + second->size - position,
			Vector2D(second->position.x, second->position.y + second->size.y) - position,
			Vector2D(second->position.x + second->size.x, second->position.y) - position
		};
		a = sort(a);

	}
	bool collides(CircleCollider* second) override { return (position - second->position).getMagnitude() <= size + second->size ? true : false; }
	bool collides(MultiCollider* second) override { 
		for (auto c : second->colliders) if (c.collides(this)) return true;
		return false;
	}
};

struct RectangleCollider : public Collider {
	Vector2D size;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h) : size({ p_w, p_h }) { position = { p_x, p_y }; }
	RectangleCollider(Vector2D p_position, Vector2D p_size) : size(p_size) { position = p_position; }

	RectangleCollider operator*(const int value) { return RectangleCollider(position.x * value, position.y * value, size.x * value, size.y * value); }

	bool collides(double p_x, double p_y) override { return(p_x >= position.x && p_y >= position.y && p_x <= position.x + size.x && p_y <= position.y + size.y); }
	bool collides(Vector2D p) override { return(p.x >= position.x && p.y >= position.y && p.x <= position.x + size.x && p.y <= position.y + size.y); }
	bool collides(RectangleCollider* second) override {
		return(collides(second->position.x, second->position.y) ||
			collides(second->position.x + second->size.x, second->position.y) ||
			collides(second->position.x, second->position.y + second->size.y) ||
			collides(second->position.x + second->size.x, second->position.y + second->size.y)) ||
			(second->collides(position.x, position.y) ||
				second->collides(position.x + size.x, position.y) ||
				second->collides(position.x, position.y + size.y) ||
				second->collides(position.x + size.x, position.y + size.y));
	}
	bool collides(CircleCollider* second) override {
		return false;
	}
	bool collides(MultiCollider* second) override {
		for (auto c : second->colliders) if (c.collides(this)) return true;
		return false;
	}
};

struct MultiCollider : public Collider {
	std::vector<Collider> colliders;
	MultiCollider() = default;
	MultiCollider(std::vector<Collider> p_colliders) : colliders(p_colliders){}
	bool collides(double x, double y) override {
		for (auto c : colliders) if (c.collides(x, y)) return true;
		return false;
	}
	bool collides(Vector2D p) override {
		for (auto c : colliders) if (c.collides(p)) return true;
		return false;
	}
	bool collides(RectangleCollider* second) override {
		for (auto c : colliders) if (c.collides(second)) return true;
		return false;
	}
	bool collides(CircleCollider* second) override {
		for (auto c : colliders) if (c.collides(second)) return true;
		return false;
	}
	bool collides(MultiCollider* second) override {
		for (auto c : second->colliders) if (c.collides(this)) return true;
		return false;
	}
};