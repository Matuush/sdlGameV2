#pragma once
#include "Collider.h"

struct RectangleCollider : public Collider {
	Vector2D size;
};

struct CircleCollider : public Collider {
	unsigned int size;
	CircleCollider() = default;
	bool collides(Vector2D p) {
		Vector2D dist = Vector2D(abs(p.x - position.x), abs(p.y - position.y));
		if (dist.getMagnitude() > size) return false;
		return true;
	}
	bool collides(double x, double y) {
		if (Vector2D { abs(x - position.x), abs(y - position.y) }.getMagnitude() > size) return false;
		return true;
	}
};
