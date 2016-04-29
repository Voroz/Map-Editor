#include "GamePolygonObject.h"

GamePolygonObject::GamePolygonObject(Vector2<float> topLeftPos, Vector2<float> size, const int flags) : GameObject(topLeftPos, size, flags){
	_vertices.push_back(Vector2<float>(_width, _height));
	_vertices.push_back(Vector2<float>(0, _height));
	_vertices.push_back(Vector2<float>(_width / 2, 0));
	_shape = new sf::ConvexShape(_vertices.size());
	
	if (_flags & Flag::outlineOnly) {
		float minSize = std::min(_width, _height);
		_shape->setOutlineThickness(-minSize*0.1);
		_shape->setOutlineColor(sf::Color(255, 255, 255));
		_shape->setFillColor(sf::Color(0, 0, 0));
	}

	//Sync shape
	sf::ConvexShape *convexShape = static_cast<sf::ConvexShape*>(_shape);
	for (int i = 0; i < _vertices.size(); i++) {
		convexShape->setPoint(i, sf::Vector2f(_vertices[i].x, _vertices[i].y));
	}
};

GamePolygonObject::~GamePolygonObject(){
	
}

bool GamePolygonObject::contains(Vector2<float> point) {
	return false;
}

void GamePolygonObject::syncShape() {
	_shape->setPosition(_position.x, _position.y);
	_shape->setOrigin(_center.x, _center.y);
}