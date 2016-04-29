#pragma once
#include "GameObject.h"

using namespace std;

class GamePolygonObject :
	public GameObject
{
public:
	GamePolygonObject(Vector2<float> topLeftPos, Vector2<float> size, const int flags = Flag::noFlag);
	virtual ~GamePolygonObject();

	bool contains(Vector2<float> point);
	void syncShape();

protected:
	vector<Vector2<float>> _vertices;
};

