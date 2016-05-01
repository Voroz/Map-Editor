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

	syncShape();
};

GamePolygonObject::~GamePolygonObject(){
	
}

bool GamePolygonObject::contains(Vector2<float> point) {
	float aLeft = _position.x + left();
	float aRight = _position.x + right();
	float aTop = _position.y + top();
	float aBottom = _position.y + bottom();

	if ((point.x > aLeft &&
		point.x < aRight &&
		point.y < aBottom &&
		point.y > aTop)) {

		//2nd Check: If the point is inside this polygon
		// Compute vectors
		Vector2<float> v0 = vertices()[1] - vertices()[0];
		Vector2<float> v1 = vertices()[2] - vertices()[0];

		// Compute dot products
		vector<float> a;
		vector<float> b;
		a.push_back(v0.x);
		a.push_back(v0.y);
		b.push_back(v0.x);
		b.push_back(v0.y);
		float dot00 = (float)inner_product(a.begin(), a.end(), b.begin(), 0);
		a.clear();
		b.clear();

		a.push_back(v0.x);
		a.push_back(v0.y);
		b.push_back(v1.x);
		b.push_back(v1.y);
		float dot01 = (float)inner_product(a.begin(), a.end(), b.begin(), 0);
		a.clear();
		b.clear();

		a.push_back(v1.x);
		a.push_back(v1.y);
		b.push_back(v1.x);
		b.push_back(v1.y);
		float dot11 = (float)inner_product(a.begin(), a.end(), b.begin(), 0);
		a.clear();
		b.clear();

		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);

		// Compute vector
		Vector2<float> v2 = point - (pos() + vertices()[0]);

		// Compute dot products
		a.push_back(v0.x);
		a.push_back(v0.y);
		b.push_back(v2.x);
		b.push_back(v2.y);
		float dot02 = (float)inner_product(a.begin(), a.end(), b.begin(), 0);
		a.clear();
		b.clear();

		a.push_back(v1.x);
		a.push_back(v1.y);
		b.push_back(v2.x);
		b.push_back(v2.y);
		float dot12 = (float)inner_product(a.begin(), a.end(), b.begin(), 0);
		a.clear();
		b.clear();

		// Compute barycentric coordinates
		float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		// Check if point is in triangle
		if ((u >= 0) && (v >= 0) && (u + v < 1)) {
			return true;
		}
	}
	return false;
}

void GamePolygonObject::update() {
	GameObject::update();
}

void GamePolygonObject::syncShape() {
	sf::ConvexShape *convexShape = static_cast<sf::ConvexShape*>(_shape);
	for (int i = 0; i < _vertices.size(); i++) {
		convexShape->setPoint(i, sf::Vector2f(_vertices[i].x, _vertices[i].y));
	}
	_shape->setPosition(_position.x, _position.y);
	_shape->setOrigin(_center.x, _center.y);
}

vector<Vector2<float>> GamePolygonObject::vertices() {
	vector<Vector2<float>> adjustedVertices;
	for (auto &i : _vertices) {
		adjustedVertices.push_back(i - _center);
	}
	return adjustedVertices;
}

int GamePolygonObject::identify() {
	return 1;
}