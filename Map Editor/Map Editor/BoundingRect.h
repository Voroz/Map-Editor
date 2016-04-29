#pragma once

#include "Vector2.h"

class BoundingRect
{
public:
	BoundingRect();
	~BoundingRect();

	Vector2<float> pos();
	Vector2<float> center();
	float top();
	float left();
	float bottom();
	float right();
	float width();
	float height();
	Vector2<float> topLeft();
	Vector2<float> topRight();
	Vector2<float> bottomRight();
	Vector2<float> bottomLeft();

	void setPos(const Vector2<float> pos);
	void setPos(const float x, const float y);
	void setCenter(const Vector2<float> center);
	void setCenter(const float x, const float y);
	void setWidth(const float width);
	void setHeight(const float height);

protected:
	Vector2<float> _position;
	Vector2<float> _center;
	float _width;
	float _height;
};

