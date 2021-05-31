#pragma once
#include <math.h>
#include <iostream>

const int floatPrecision = 15;

struct Vector2D {
	double x, y;
	Vector2D() : x(0), y(0) {};
	Vector2D(double p_x, double p_y) : x(p_x), y(p_y) {}
	Vector2D(int p_x, int p_y) : x((double)p_x), y((double)p_y) {}
	Vector2D(unsigned int p_x, unsigned int p_y) : x((double)p_x), y((double)p_y) {}

	Vector2D limit(double limit) {
		if (getMagnitude() > limit) setMagnitude(limit);
		return Vector2D(x, y);
	}
	Vector2D setMagnitude(double limit) {
		double aah = getMagnitude();
		if (aah != 0) {
			x = x / aah * limit;
			y = y / aah * limit;
		}
		else {
			x = sqrt(limit * limit / 2);
			y = x;
		}
		return Vector2D(x, y);
	}
	Vector2D normalize() const { return Vector2D(x / getMagnitude(), y / getMagnitude()); }

	void operator=(Vector2D second) { x = second.x; y = second.y; }
	void operator=(double second) { x = second; y = second; }
	void operator*=(Vector2D second) { x *= second.x; y *= second.y; }
	void operator*=(double second) { x *= second; y *= second; }
	void operator+=(Vector2D second) { x += second.x; y += second.y; }
	void operator-=(Vector2D second) { x -= second.x; y -= second.y; }
	Vector2D operator+(Vector2D second) const { return Vector2D(x + second.x, y + second.y); }
	Vector2D operator+(int second) const { return Vector2D(x + second, y + second); }
	Vector2D operator-(Vector2D second) const { return Vector2D(x - second.x, y - second.y); }
	Vector2D operator-(int second) const { return Vector2D(x - second, y - second); }
	Vector2D operator*(Vector2D second) const { return Vector2D(x * second.x, y * second.y); }
	Vector2D operator*(int second) const { return Vector2D(x * second, y * second); }
	Vector2D operator*(unsigned int second) const { return Vector2D(x * second, y * second); }
	Vector2D operator*(double second) const { return Vector2D(x * second, y * second); }
	Vector2D operator/(Vector2D second) const { return Vector2D(x / second.x, y / second.y); }
	Vector2D operator/(int second) const { return Vector2D(x / second, y / second); }
	Vector2D operator/(double second) const { return Vector2D(x / second, y / second); }


	bool operator>=(Vector2D second) const { return getMagnitude() >= second.getMagnitude(); }
	bool operator>(Vector2D second) const { return getMagnitude() > second.getMagnitude(); }
	bool operator<=(Vector2D second) const { return getMagnitude() <= second.getMagnitude(); }
	bool operator<(Vector2D second) const { return getMagnitude() < second.getMagnitude(); }
	bool operator>=(double second) const { return getMagnitude() >= second; }
	bool operator>(double second) const { return getMagnitude() > second; }
	bool operator<=(double second) const { return getMagnitude() <= second; }
	bool operator<(double second) const { return getMagnitude() < second; }
	bool operator==(double second) const { return getMagnitude() * pow(10, floatPrecision) == second; }
	bool operator==(Vector2D second) const {
		return round(x * pow(10, floatPrecision)) == round(second.x * pow(10, floatPrecision)) &&
			round(y * pow(10, floatPrecision)) == round(second.y * pow(10, floatPrecision));
	}
	bool operator!=(Vector2D second) const {
		return round(x * pow(10, floatPrecision)) != round(second.x * pow(10, floatPrecision)) ||
			round(y * pow(10, floatPrecision)) != round(second.y * pow(10, floatPrecision));
	}

	double getMagnitude() const { return sqrt(x * x + y * y); }
	double getAngle() const { return sqrt(atan(y/x)); }
	static Vector2D fromPolar(double magnitude, double angle) { return Vector2D(cos(angle) * magnitude, sin(angle) * magnitude); }
};