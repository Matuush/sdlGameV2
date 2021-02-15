#pragma once

struct KeyState {
	bool w = 0, s = 0, a = 0, d = 0;
	KeyState() = default;
	void zeroify() {
		w = 0, s = 0, a = 0, d = 0;
	}
};