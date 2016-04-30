#pragma once
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"
#include "Controls.h"
#include "Ui.h"
#include "MyView.h"
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
	int align(int value, int size);
	bool isInWorldrect(GameObject* gameObj);

private:
	vector<GameObject*> _gameObjectVector;
	GameObject* _mouseObject;
	sf::RenderWindow *_window;
	Controls *_controls;
	Ui *_ui;
	MyView *_view;
	Vector2<float> _worldSize;
	sf::RectangleShape _worldRectshape;
	Vector2<float> _savedMousePos;
};

