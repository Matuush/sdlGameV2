#pragma once
#include <SDL.h>

#include "Entity.h"

#include "Constants.h"

struct Button : public Entity{
	const char* text;
	Button();
	Button(int x, int y, const char* p_text);

	void onClick();
};
