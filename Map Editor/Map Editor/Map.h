#pragma once
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"
#include "Player.h"
#include "Controls.h"
#include "Ui.h"
#include "MyView.h"
#include <deque>
#include <iostream>

using namespace std;

class Ui;

class Map
{
public:
	Map(sf::RenderWindow &window, Controls &controls);
	~Map();
	void setUi(Ui &ui);
	void update();
	void render();
	void sync();
	deque<GameObject*> mouseOnObject();
	int align(int value, int size);
	bool isInWorldrect(GameObject* gameObj);
	bool isInWorldXrect(GameObject* gameObj);
	bool isInWorldYrect(GameObject* gameObj);
	void matchWorldXToObjects();
	void matchWorldYToObjects();
	deque<GameObject*>& gameObjects();
	bool objectTypeExists(int type);

private:
	deque<GameObject*> _gameObjectVector;
	GameObject* _mouseObject;
	sf::RenderWindow *_window;
	Controls *_controls;
	Ui *_ui;
	MyView *_view;
	Vector2<int*> _worldSize;
	sf::RectangleShape _worldRectshape;
	Vector2<float> _savedMousePos;
};

