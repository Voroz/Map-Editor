#include "GamePolygonObject.h"

GamePolygonObject::GamePolygonObject(const int physicsType, Vector2<float> topLeftPos, Vector2<float> size, const float mass, const float bouncyness, Vector2<float> gravityMultiplier, Vector2<float> point1Offset, Vector2<float> point2Offset, Vector2<float> point3Offset, const int flags) : GameObject(physicsType, topLeftPos, size, mass, bouncyness, gravityMultiplier, flags){
	_point1Offset = point1Offset;
	_point2Offset = point2Offset;
	_point3Offset = point3Offset;
	_vertices.push_back(Vector2<float>(_width * _point1Offset.x, _height * _point1Offset.y));
	_vertices.push_back(Vector2<float>(_width * _point2Offset.x, _height * _point2Offset.y));
	_vertices.push_back(Vector2<float>(_width * _point3Offset.x, _height * _point3Offset.y));
	_shape = new sf::ConvexShape(_vertices.size());

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

Vector2<float> GamePolygonObject::point1Offset() {
	return _point1Offset;
}
Vector2<float> GamePolygonObject::point2Offset() {
	return _point2Offset;
}
Vector2<float> GamePolygonObject::point3Offset() {
	return _point3Offset;
}

void GamePolygonObject::update() {
	GameObject::update();
}

void GamePolygonObject::syncShape() {
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

void GamePolygonObject::setVertices(Vector2<float> v1, Vector2<float> v2, Vector2<float> v3) {
	assert(v1.x >= 0 && v1.x <= 1 && v1.y >= 0 && v1.y <= 1
		&& v2.x >= 0 && v2.x <= 1 && v2.y >= 0 && v2.y <= 1
		&& v3.x >= 0 && v3.x <= 1 && v3.y >= 0 && v3.y <= 1);

	_vertices[0] = Vector2<float>(_width * v1.x, _height * v1.y);
	_vertices[1] = Vector2<float>(_width * v2.x, _height * v2.y);
	_vertices[2] = Vector2<float>(_width * v3.x, _height * v3.y);

	sf::ConvexShape *convexShape = static_cast<sf::ConvexShape*>(_shape);
	for (int i = 0; i < _vertices.size(); i++) {
		convexShape->setPoint(i, sf::Vector2f(_vertices[i].x, _vertices[i].y));
	}
}

int GamePolygonObject::identify() {
	return 1;
}