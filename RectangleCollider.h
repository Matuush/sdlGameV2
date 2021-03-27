#pragma once
#include "Constants.h"

struct RectangleCollider {
	double x, y, w, h;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h) : x(p_x), y(p_y), w(p_w), h(p_h) {}
	RectangleCollider(Vector2D position, Vector2D size) : x(position.x), y(position.y), w(size.x), h(size.y) {}

	bool collides(RectangleCollider* second) {
		return(collides(second->x, second->y) ||
			collides(second->x + second->w, second->y) ||
			collides(second->x, second->y + second->h) ||
			collides(second->x + second->w, second->y + second->h)) ||
			(second->collides(x, y) ||
				second->collides(x + w, y) ||
				second->collides(x, y + h) ||
				second->collides(x + w, y + h));
	}
	bool collides(double p_x, double p_y) { return(p_x >= x && p_y >= y && p_x <= x + w && p_y <= y + h); }
	bool collides(Vector2D* p) { return(p->x >= x && p->y >= y && p->x <= x + w && p->y <= y + h); }
};