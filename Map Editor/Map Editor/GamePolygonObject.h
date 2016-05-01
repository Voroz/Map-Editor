#pragma once
#include "GameObject.h"
#include <numeric>

using namespace std;

class GamePolygonObject :
	public GameObject
{
public:
	GamePolygonObject(Vector2<float> topLeftPos, Vector2<float> size, const int flags = Flag::noFlag);
	virtual ~GamePolygonObject();

	bool contains(Vector2<float> point);
	void syncShape();
	vector<Vector2<float>> vertices();
	int identify();

protected:
	vector<Vector2<float>> _vertices;
};

