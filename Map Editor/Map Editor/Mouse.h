#pragma once
#include "Vector2.h"

struct Mouse {
	Vector2<float> pos = Vector2<float>(0, 0);
	bool leftDown = false;
	bool rightDown = false;
};