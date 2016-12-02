#pragma once

enum Flag {
	noFlag = (1 << 0),
	fallsWhenTouched = (1 << 1),
	deadly = (1 << 2),
	outlineOnly = (1 << 3),
	invertsGravityPlayer = (1 << 4),
	invertsGravityObject = (1 << 4),
};