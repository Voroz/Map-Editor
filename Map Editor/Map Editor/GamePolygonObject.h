#pragma once
#include "GameObject.h"
#include <numeric>

using namespace std;

class GamePolygonObject :
	public GameObject
{
public:
	GamePolygonObject(Vector2<float> topLeftPos, Vector2<float> size, Vector2<float> point1Offset = Vector2<float>(0, 0), Vector2<float> point2Offset = Vector2<float>(0, 0), Vector2<float> point3Offset = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	virtual ~GamePolygonObject();

	bool contains(Vector2<float> point);
	Vector2<float> point1Offset();
	Vector2<float> point2Offset();
	Vector2<float> point3Offset();
	void syncShape();
	void update();
	vector<Vector2<float>> vertices();
	int identify();

protected:
	Vector2<float> _point1Offset;
	Vector2<float> _point2Offset;
	Vector2<float> _point3Offset;
	vector<Vector2<float>> _vertices;
};

