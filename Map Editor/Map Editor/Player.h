#pragma once
#include "GameRectObject.h"


class Player :
	public GameRectObject
{
public:
	Player(Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0));
	Player(float x, float y, float width = 0, float height = 0);
	~Player();

	int identify();
};

