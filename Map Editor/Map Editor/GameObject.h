#pragma once
#include "BoundingRect.h"
#include "SFML/Graphics.hpp"

enum Flag {
	noFlag = (1 << 0),
	fallsWhenTouched = (1 << 1),
	deadly = (1 << 2),
	outlineOnly = (1 << 3),
};

class GameObject :
	public virtual BoundingRect
{
public:
	friend class Game;
	GameObject(Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	GameObject(float x, float y, float width = 0, float height = 0, const int flags = Flag::noFlag);
	~GameObject();

	int flags();
	sf::Shape* shape();

protected:
	//Functions
	virtual void syncShape() = 0;

	//Attributes
	int _flags;
	sf::Shape *_shape;
};

