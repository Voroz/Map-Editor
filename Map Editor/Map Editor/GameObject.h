#pragma once
#include "BoundingRect.h"
#include "SFML/Graphics.hpp"
#include "Flag.h"

class GameObject :
	public virtual BoundingRect
{
public:
	friend class Game;
	GameObject(Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	GameObject(float x, float y, float width = 0, float height = 0, const int flags = Flag::noFlag);
	~GameObject();

	virtual bool contains(Vector2<float> point) = 0;
	int flags();
	sf::Shape* shape();
	virtual void update();
	virtual int identify() = 0;

protected:
	//Functions
	virtual void syncShape() = 0;

	//Attributes
	int _flags;
	sf::Shape *_shape;
};

