#pragma once
#include "GameObject.h"

using namespace std;

class GamePolygonObject :
	public GameObject
{
public:
	GamePolygonObject(Vector2<float> topLeftPos, vector<Vector2<float>> pointVector, const int flags = Flag::noFlag);
	virtual ~GamePolygonObject();

	void syncShape();

protected:
	vector<Vector2<float>> _vertices;
};

