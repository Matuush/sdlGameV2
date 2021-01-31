#pragma once
#include "Vector2D.h"

#include "Constants.h"

struct RectangleCollider {
	double x, y, w, h;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h);

	bool collides(RectangleCollider* second);
	bool collides(double x, double y);
	bool collides(Vector2D* p);
};