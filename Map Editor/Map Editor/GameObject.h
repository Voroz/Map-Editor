#pragma once
#include "BoundingRect.h"
#include "SFML/Graphics.hpp"
#include "Flag.h"

class GameObject :
	public virtual BoundingRect
{
public:
	friend class Game;
	GameObject(const int physicsType, Vector2<float> pos = Vector2<float>(0, 0), Vector2<float> size = Vector2<float>(0, 0), const float mass = 1, const float bouncyness = 0, Vector2<float> gravityMultiplier = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	GameObject(const int physicsType, float x, float y, float width = 0, float height = 0, const float mass = 1, const float bouncyness = 0, Vector2<float> gravityMultiplier = Vector2<float>(0, 0), const int flags = Flag::noFlag);
	~GameObject();

	virtual bool contains(Vector2<float> point) = 0;
	float mass() const;
	float bouncyness() const;
	int flags();
	int physicsType();
	Vector2<float> gravityMultiplier();
	sf::Shape* shape();
	virtual void update();
	virtual int identify() = 0;
	void setMass(float mass);
	void setBouncyness(float bouncyness);
	void setGravityMultiplier(Vector2<float> gravityMultiplier);
	void setFlags(int flags);

protected:
	//Functions
	virtual void syncShape() = 0;

	//Attributes
	float _mass;
	float _bouncyness;
	Vector2<float> _gravityMultiplier;
	int _physicsType;
	int _flags;
	sf::Shape *_shape;
};

