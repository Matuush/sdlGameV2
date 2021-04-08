#pragma once
#include "Vector2D.h"
#include <vector>

struct RectangleCollider;
struct CircleCollider;
struct MultiCollider;

struct Collider {
	Vector2D position;
	virtual bool collides(double x, double y) = 0;
	virtual bool collides(Vector2D p) = 0;
	virtual bool collides(RectangleCollider* second) = 0;
	virtual bool collides(CircleCollider* second) = 0;
	virtual bool collides(MultiCollider* second) = 0;
	bool collides(Collider* second) { return false; }
};

struct CircleColider : public Collider {
	unsigned int size;
	CircleCollider() = default;
	CircleCollider(Vector2D p_position, unsigned int p_size);
	bool collides(double x, double y) override;
	bool collides(Vector2D p) override;
	bool collides(RectangleColider* second) override;
	bool collides(CircleColider* second) override;
	bool collides(MultiCollider* second) override;
};
struct RectangleColider : public Collider {
	Vector2D size;
	RectangleCollider() = default;
	RectangleCollider(double p_x, double p_y, double p_w, double p_h) : size({ p_w, p_h }) { position = { p_x, p_y }; }
	RectangleCollider(Vector2D p_position, Vector2D p_size) : size(p_size) { position = p_position; }
	RectangleCollider operator*(const int value) { return RectangleCollider(position.x * value, position.y * value, size.x * value, size.y * value); }
	bool collides(double x, double y) override;
	bool collides(Vector2D p) override;
	bool collides(RectangleColider* second) override;
	bool collides(CircleColider* second) override;
	bool collides(MultiCollider* second) override;
};
struct MultiCollider : public Collider {
	std::vector<Collider> colliders;
	MultiCollider() = default;
	MultiCollider(std::vector<Collider> p_colliders) : colliders(p_colliders) {}
	bool collides(double x, double y) override;
	bool collides(Vector2D p) override;
	bool collides(RectangleColider* second) override;
	bool collides(CircleColider* second) override;
	bool collides(MultiCollider* second) override;
};

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

// CircleCollider
CircleCollider::CircleCollider(Vector2D p_position, unsigned int p_size) { position = p_position; size = p_size; }
bool CircleCollider::collides(Vector2D p) { return collides(p.x, p.y); }
bool CircleCollider::collides(double x, double y) { return Vector2D{ abs(x - position.x), abs(y - position.y) }.getMagnitude() <= size ? true : false; }
bool CircleCollider::collides(RectangleCollider* second) { return second->collides(this); }
bool CircleCollider::collides(CircleCollider* second) { return (position - second->position).getMagnitude() <= size + second->size ? true : false; }
bool CircleCollider::collides(MultiCollider* second) {
	for (Collider c : second->colliders) if (c.collides(this)) return true;
	return false;
}

// RectangleCollider
bool RectangleCollider::collides(double p_x, double p_y) { return(p_x >= position.x && p_y >= position.y && p_x <= position.x + size.x && p_y <= position.y + size.y); }
bool RectangleCollider::collides(Vector2D p) { return(p.x >= position.x && p.y >= position.y && p.x <= position.x + size.x && p.y <= position.y + size.y); }
bool RectangleCollider::collides(RectangleCollider* second) {
	return(collides(second->position.x, second->position.y) ||
		collides(second->position.x + second->size.x, second->position.y) ||
		collides(second->position.x, second->position.y + second->size.y) ||
		collides(second->position.x + second->size.x, second->position.y + second->size.y)) ||
		(second->collides(position.x, position.y) ||
			second->collides(position.x + size.x, position.y) ||
			second->collides(position.x, position.y + size.y) ||
			second->collides(position.x + size.x, position.y + size.y));
}
bool RectangleCollider::collides(CircleCollider* second) {
	if (collides(second->position)) return true;
	std::vector<Vector2D> a = {
		position - second->position,
		position + size - second->position,
		Vector2D(position.x, position.y + size.y) - second->position,
		Vector2D(position.x + size.x, position.y) - second->position
	};
	a = sort(a);
}
bool RectangleCollider::collides(MultiCollider* second) {
	for (Collider c : second->colliders) if (c.collides(this)) return true;
	return false;
}

// MultiCollider
bool MultiCollider::collides(double x, double y) {
	for (Collider c : colliders) if (c.collides(x, y)) return true;
	return false;
}
bool MultiCollider::collides(Vector2D p) {
	for (Collider c : colliders) if (c.collides(p)) return true;
	return false;
}
bool MultiCollider::collides(RectangleCollider* second) {
	for (Collider c : colliders) if (c.collides(second)) return true;
	return false;
}
bool MultiCollider::collides(CircleCollider* second) {
	for (Collider c : colliders) if (c.collides(second)) return true;
	return false;
}
bool MultiCollider::collides(MultiCollider* second) {
	for (Collider c : second->colliders) if (c.collides(this)) return true;
	return false;
}