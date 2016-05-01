#include "GameRectObject.h"

GameRectObject::GameRectObject(Vector2<float> pos, Vector2<float> size, const int flags) : GameObject(pos, size, flags) {
	_shape = new sf::RectangleShape;

	if (_flags & Flag::outlineOnly) {
		float minSize = std::min(_width, _height);
		_shape->setOutlineThickness(-minSize*0.1);
		_shape->setOutlineColor(sf::Color(255, 255, 255));
		_shape->setFillColor(sf::Color(0, 0, 0));
	}
};
GameRectObject::GameRectObject(float x, float y, float width, float height, const int flags) : GameObject(x, y, width, height, flags) {
	_shape = new sf::RectangleShape;

	if (_flags & Flag::outlineOnly) {
		float minSize = std::min(_width, _height);
		_shape->setOutlineThickness(-minSize*0.1);
		_shape->setOutlineColor(sf::Color(255, 255, 255));
		_shape->setFillColor(sf::Color(0, 0, 0));
	}
};

GameRectObject::~GameRectObject(){ 
	
}

bool GameRectObject::contains(Vector2<float> point) {
	float x = point.x;
	float y = point.y;
	float aLeft = pos().x + left();
	float aRight = pos().x + right();
	float aTop = pos().y + top();
	float aBottom = pos().y + bottom();

	return (x > aLeft && x < aRight &&
		y > aTop && y < aBottom);
}

void GameRectObject::syncShape() {
	_shape->setPosition(_position.x, _position.y);
	_shape->setOrigin(_center.x, _center.y);
	sf::RectangleShape* rectShape = static_cast<sf::RectangleShape*>(_shape);
	rectShape->setSize(sf::Vector2f(_width, _height));
}

int GameRectObject::identify() {
	return 0;
}