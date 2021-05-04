#pragma once
#include "Vector2D.hpp"
struct KeyState {
	bool w = 0, s = 0, a = 0, d = 0;
	Vector2D lcPos = DEFAULT_BULLET_POSITION;
	KeyState() = default;
	void zeroify() { w = 0, s = 0, a = 0, d = 0; }
};