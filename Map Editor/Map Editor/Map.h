#pragma once
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"
#include "Controls.h"
#include "Ui.h"
#include <iostream>

using namespace std;

class Map
{
public:
	Map(sf::RenderWindow &window, Controls &controls, Ui &ui);
	~Map();
	void update();
	void render();
	vector<GameObject*> mouseOnObject();

private:
	vector<GameObject*> _gameObjectVector;
	sf::RenderWindow *_window;
	Controls *_controls;
	Ui *_ui;
};

