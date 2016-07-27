#pragma once
#include "GameObject.h"

class GameRectObject :
	public GameObject
{
public:
	GameRectObject(const int physicsType, Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0), const float mass = 1, const float bouncyness = 0, const int flags = Flag::noFlag);
	GameRectObject(const int physicsType, float x, float y, float width = 0, float height = 0, const float mass = 1, const float bouncyness = 0, const int flags = Flag::noFlag);
	virtual ~GameRectObject();

	bool contains(Vector2<float> point);
	void syncShape();
	virtual int identify();
};

