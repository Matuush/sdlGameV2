#pragma once
#include "Button.h"
struct Page {
	std::vector<Button> buttons;
	LOOP_TYPE loopType;
	Page(LOOP_TYPE p_loopType, std::vector<Button> p_buttons) : loopType(p_loopType), buttons(p_buttons) {}
};