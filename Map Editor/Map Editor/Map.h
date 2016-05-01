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
	void sync();
	vector<GameObject*> mouseOnObject();
	int align(int value, int size);
	bool isInWorldrect(GameObject* gameObj);
	bool isInWorldXrect(GameObject* gameObj);
	bool isInWorldYrect(GameObject* gameObj);
	void matchWorldXToObjects();
	void matchWorldYToObjects();
	vector<GameObject*>& gameObjects();

private:
	vector<GameObject*> _gameObjectVector;
	GameObject* _mouseObject;
	sf::RenderWindow *_window;
	Controls *_controls;
	Ui *_ui;
	MyView *_view;
	Vector2<int*> _worldSize;
	sf::RectangleShape _worldRectshape;
	Vector2<float> _savedMousePos;
};

