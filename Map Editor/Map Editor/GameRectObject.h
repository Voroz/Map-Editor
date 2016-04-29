#pragma once
#include "GameObject.h"

class GameRectObject :
	public GameObject
{
public:
	GameRectObject(Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	GameRectObject(float x, float y, float width = 0, float height = 0, const int flags = Flag::noFlag);
	virtual ~GameRectObject();

	void syncShape();
};

