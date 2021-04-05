#pragma once
#include "Vector2D.h"

struct Collider {
	Vector2D position;
	Collider() = default;
	virtual bool collides(double x, double y) { }
	virtual bool collides(Vector2D p) { }
	virtual bool collides(RectangleCollider* second) { }
	virtual bool collides(CircleCollider* second) { }
};

struct CircleCollider : public Collider {
	unsigned int size;
	CircleCollider() = default;
	CircleCollider(Vector2D p_position, unsigned int p_size) : size(p_size) {
		position = p_position;
	}
	bool collides(CircleCollider* second) {
		return (position - second->position).getMagnitude() <= size + second->size ? true : false;
	}
	bool collides(Vector2D p) override { return collides(p.x, p.y); }
	bool collides(double x, double y) override {
		return Vector2D{ abs(x - position.x), abs(y - position.y) }.getMagnitude() <= size ? true : false;
	}
};

struct RectangleCollider : public Collider {
	Vector2D size;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h) : size({ p_w, p_h }) { position = { p_x, p_y }; }
	RectangleCollider(Vector2D p_position, Vector2D p_size) : size(p_size) { position = p_position; }

	RectangleCollider operator*(const int value) { return RectangleCollider(position.x * value, position.y * value, size.x * value, size.y * value); }

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
	bool collides(double p_x, double p_y) override { return(p_x >= position.x && p_y >= position.y && p_x <= position.x + size.x && p_y <= position.y + size.y); }
	bool collides(Vector2D p) override { return(p.x >= position.x && p.y >= position.y && p.x <= position.x + size.x && p.y <= position.y + size.y); }
};