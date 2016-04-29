#pragma once

enum Flag {
	noFlag = (1 << 0),
	fallsWhenTouched = (1 << 1),
	deadly = (1 << 2),
	outlineOnly = (1 << 3),
};