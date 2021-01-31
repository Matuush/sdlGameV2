#include "RectangleCollider.h"

RectangleCollider::RectangleCollider(double p_x, double p_y, double p_w, double p_h) : x(p_x), y(p_y), w(p_w), h(p_h) {}

bool RectangleCollider::collides(RectangleCollider* second) {
	return(collides(second->x, second->y) || 
		collides(second->x + second->w, second->y) ||
		collides(second->x, second->y + second->h) ||
		collides(second->x + second->w, second->y + second->h));
}

bool RectangleCollider::collides(double p_x, double p_y) { return(p_x > x && p_y > y && p_x < x + w && p_y < y + h); }

bool RectangleCollider::collides(Vector2D* p) { return(p->x > x && p->y > y && p->x < x + w && p->y < y + h); }