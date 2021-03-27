#pragma once
#include <math.h>

const int floatPrecision = 8;

struct Vector2D {
	double x, y;
	Vector2D() = default;
	Vector2D(double p_x, double p_y) : x(p_x), y(p_y) {}
	Vector2D(int p_x, int p_y) : x((double)p_x), y((double)p_y) {}

	void limit(double limit) {
		if (getMagnitude() > limit) setMagnitude(limit);
	}
	void setMagnitude(double limit) {
		x = x / getMagnitude() * limit;
		y = y / getMagnitude() * limit;
	}
	Vector2D normalize() const {
		return Vector2D(x / getMagnitude(), y / getMagnitude());
	}

	Vector2D operator+(Vector2D second) const { return Vector2D(x + second.x, y + second.y); }
	Vector2D operator+(int second) const { return Vector2D(x + second, y + second); }
	Vector2D operator-(Vector2D second) const { return Vector2D(x - second.x, y - second.y); }
	Vector2D operator-(int second) const { return Vector2D(x - second, y - second); }
	Vector2D operator*(Vector2D second) const { return Vector2D(x * second.x, y * second.y); }
	Vector2D operator*(int second) const { return Vector2D(x * second, y * second); }
	Vector2D operator/(Vector2D second) const { return Vector2D(x / second.x, y / second.y); }
	Vector2D operator/(int second) const { return Vector2D(x / second, y / second); }
	bool operator==(Vector2D second) const {
		return round(x * pow(10, floatPrecision)) == round(second.x * pow(10, floatPrecision)) && 
			round(y * pow(10, floatPrecision)) == round(second.y * pow(10, floatPrecision));
	}
	bool operator>=(Vector2D second) const {
		return getMagnitude() >= second.getMagnitude();
	}
	bool operator>(Vector2D second) const {
		return getMagnitude() > second.getMagnitude();
	}
	bool operator<=(Vector2D second) const {
		return getMagnitude() <= second.getMagnitude();
	}
	bool operator<(Vector2D second) const {
		return getMagnitude() < second.getMagnitude();
	}

	Vector2D operator*(double second) const { return Vector2D(x * second, y * second); }
	Vector2D operator/(double second) const { return Vector2D(x / second, y / second); }
	bool operator>=(double second) const {
		return getMagnitude() >= second;
	}
	bool operator>(double second) const {
		return getMagnitude() > second;
	}
	bool operator<=(double second) const {
		return getMagnitude() <= second;
	}
	bool operator<(double second) const {
		return getMagnitude() < second;
	}

	double getMagnitude() const { return sqrt(x * x + y * y); }
	double getAngle() const { return sqrt(atan(y/x)); }
	static Vector2D fromPolar(double magnitude, double angle) { return Vector2D(cos(angle) * magnitude, sin(angle) * magnitude); }
};