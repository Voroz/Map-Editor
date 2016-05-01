#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <fstream>
#include "Flag.h"
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"

using namespace std;

class Ui
{
public:
	Ui(sf::RenderWindow& window);
	~Ui();
	int& type();
	int& flags();
	Vector2<float>& objectSize();
	int* worldSize();
	void setTooltip(string tooltip);
	void update(vector<GameObject*> &gameObjectVector);
	void render();
	bool mouseOnWindow();
	bool objectValueChanged();

private:
	void saveValues();
	bool _fallsWhenTouched;
	bool _deadly;
	bool _outlineOnly;
	int _objectSize[2];
	int _type;
	int _flags;
	int _worldSize[2];
	char _tooltip[40];
	int _savedFlags;
	Vector2<float> _savedObjectSize;
	int _savedType;

	char _filename[20];
};

