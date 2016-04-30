#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "Flag.h"

using namespace std;

class Ui
{
public:
	Ui(sf::RenderWindow& window);
	~Ui();
	int& type();
	int& flags();
	Vector2<float>& size();
	void update();
	void render();
	bool mouseOnWindow();
	bool valueChanged();

private:
	void saveValues();
	bool _fallsWhenTouched;
	bool _deadly;
	bool _outlineOnly;
	int _size[2];
	int _type;
	int _flags;
	int _savedFlags;
	Vector2<float> _savedSize;
	int _savedType;
};

