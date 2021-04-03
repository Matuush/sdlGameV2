#pragma once
#include "Collider.h"

struct CircleCollider : public Collider {
	unsigned int size;
};

struct RectangleCollider : public Collider{
	Vector2D size;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h) : size({ p_w, p_h }) { position = { p_x, p_y }; }
	RectangleCollider(Vector2D p_position, Vector2D p_size) : size(p_size) { position = p_position; }

	RectangleCollider operator*(const int value) { return RectangleCollider(position.x * value, position.y * value, size.x * value, size.y * value); }

	bool collides(RectangleCollider* second) {
		return(collides(second->position.x, second->position.y) ||
			collides(second->position.x + second->size.x, second->position.y) ||
			collides(second->position.x, second->position.y + second->size.y) ||
			collides(second->position.x + second->size.x, second->position.y + second->size.y)) ||
			(second->collides(position.x, position.y) ||
				second->collides(position.x + size.x, position.y) ||
				second->collides(position.x, position.y + size.y) ||
				second->collides(position.x + size.x, position.y + size.y));
	}
	bool collides(double p_x, double p_y) { return(p_x >= position.x && p_y >= position.y && p_x <= position.x + size.x && p_y <= position.y + size.y); }
	bool collides(Vector2D p) { return(p.x >= position.x && p.y >= position.y && p.x <= position.x + size.x && p.y <= position.y + size.y); }
};