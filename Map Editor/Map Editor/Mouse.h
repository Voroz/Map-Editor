#pragma once
#include "Vector2.h"
#include "SFML/Graphics.hpp"

class Mouse {
public:
	Mouse(sf::RenderWindow &window);
	~Mouse();
	Vector2<float> pos();
	Vector2<float> worldPos();
	bool left();
	bool right();
	int wheel();
	bool wheelClick();
	void setPos(Vector2<float> pos);
	void setLeft(bool left);
	void setRight(bool right);
	void setWheel(int step);
	void setWheelClick(bool down);

private:
	sf::RenderWindow *_window;
	Vector2<float> _pos;
	bool _left;
	bool _right;
	int _wheel;
	bool _wheelClick;
};