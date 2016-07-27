#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "Vector2.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <fstream>
#include <deque>
#include "Flag.h"
#include "Map.h"
#include "GameObject.h"
#include "GameRectObject.h"
#include "GamePolygonObject.h"
#include "Player.h"

using namespace std;

class Map;

class Ui
{
public:
	Ui(sf::RenderWindow& window, Map &map);
	~Ui();
	int& objectType();
	int& physicsType();
	float& mass();
	float& bouncyness();
	int& flags();
	Vector2<float>& objectSize();
	int* worldSize();
	float* point1();
	float* point2();
	float* point3();
	void setTooltip(string tooltip);
	void update();
	void render();
	bool mouseOnWindow();
	bool objectValueChanged();
	void saveFile(string filepath);
	void loadFile(string filepath);

private:
	Map *_map;
	void saveValues();
	float _mass;
	float _bouncyness;
	bool _fallsWhenTouched;
	bool _deadly;
	bool _outlineOnly;
	bool _invertsGravity;
	int _objectSize[2];
	float _point1[2];
	float _point2[2];
	float _point3[2];
	int _objectType;
	int _physicsType;
	int _flags;
	int _worldSize[2];
	char _tooltip[40];
	float _savedMass;
	float _savedBouncyness;
	int _savedFlags;
	Vector2<float> _savedObjectSize;
	int _savedObjectType;
	int _savedPhysicsType;
	float _savedPoint1[2];
	float _savedPoint2[2];
	float _savedPoint3[2];
	bool _opened;

	bool _inputSavefile;
	bool _inputLoadfile;
	char _filename[20];
	vector<string> _recentFiles;
};

