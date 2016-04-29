#pragma once
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"

using namespace std;

class Map
{
public:
	Map(sf::RenderWindow &window);
	~Map();
	void update();
	void render();

private:
	vector<GameObject*> _gameObjectVector;
	sf::RenderWindow *_window;
};

