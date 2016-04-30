#pragma once
#include "Mouse.h"

class Controls {
public:
	Controls(sf::RenderWindow &window);
	~Controls();
	Mouse& mouse();
	bool lShift();
	void setLShift(bool down);

private:
	Mouse _mouse;
	bool _lShift;
};