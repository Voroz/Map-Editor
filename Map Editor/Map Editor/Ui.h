#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>

using namespace std;

enum Flag {
	noFlag = (1 << 0),
	fallsWhenTouched = (1 << 1),
	deadly = (1 << 2),
	outlineOnly = (1 << 3),
};

class Ui
{
public:
	Ui(sf::RenderWindow& window);
	~Ui();
	int& type();
	int& flags();
	Vector2<int>& size();
	void update();
	void render();

private:
	bool _fallsWhenTouched;
	bool _deadly;
	bool _outlineOnly;
	int _size[2];
	int _type;
	int _flags;
};

