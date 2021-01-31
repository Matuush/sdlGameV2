#pragma once
#include <math.h>

#include "Constants.h"

struct Vector2D {
	double x, y;
	Vector2D() = default;
	Vector2D(double p_x, double p_y) : x(p_x), y(p_y) {}

	Vector2D operator+(Vector2D second) { return Vector2D(x + second.x, y + second.y); }
	Vector2D operator-(Vector2D second) { return Vector2D(x - second.x, y - second.y); }
	Vector2D operator*(Vector2D second) { return Vector2D(x * second.x, y * second.y); }
	Vector2D operator/(Vector2D second) { return Vector2D(x / second.x, y / second.y); }
	bool operator==(Vector2D second) { 
		return round(x * pow(10, floatPrecision)) == round(second.x * pow(10, floatPrecision)) && 
			round(y * pow(10, floatPrecision)) == round(second.y * pow(10, floatPrecision));
	}

	double getMagnitude() { return sqrt(x * x + y * y); }
	double getAngle() { return sqrt(atan(y/x)); }
	static Vector2D fromPolar(double magnitude, double angle) { return Vector2D(cos(angle) * magnitude, sin(angle) * magnitude); }
};