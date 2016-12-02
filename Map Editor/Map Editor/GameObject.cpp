#include "GameObject.h"

GameObject::GameObject(const int physicsType, Vector2<float> pos, Vector2<float> size, const float mass, const float bouncyness, Vector2<float> gravityMultiplier, const int flags){
	_physicsType = physicsType;
	_flags = flags;
	_position = pos;
	_width = size.x;
	_height = size.y;
	_center.x = _width / 2;
	_center.y = _height / 2;
	_mass = mass;
	_bouncyness = bouncyness;
	_gravityMultiplier = gravityMultiplier;
}
GameObject::GameObject(const int physicsType, float x, float y, float width, float height, const float mass, const float bouncyness, Vector2<float> gravityMultiplier, const int flags){
	_physicsType = physicsType;
	_flags = flags;
	_position = Vector2<float>(x, y);
	_width = width;
	_height = height;
	_center.x = _width / 2;
	_center.y = _height / 2;
	_mass = mass;
	_bouncyness = bouncyness;
	_gravityMultiplier = gravityMultiplier;
}
GameObject::~GameObject() {
	delete _shape;
}
int GameObject::flags() {
	return _flags;
}
float GameObject::mass() const {
	return _mass;
}
float GameObject::bouncyness() const {
	return _bouncyness;
}
int GameObject::physicsType() {
	return _physicsType;
}
Vector2<float> GameObject::gravityMultiplier() {
	return _gravityMultiplier;
}
sf::Shape* GameObject::shape() {
	return _shape;
}
void GameObject::update() {
	syncShape();
}
void GameObject::setMass(float mass) {
	_mass = mass;
}
void GameObject::setBouncyness(float bouncyness) {
	_bouncyness = bouncyness;
}
void GameObject::setGravityMultiplier(Vector2<float> gravityMultiplier) {
	_gravityMultiplier = gravityMultiplier;
}
void GameObject::setFlags(int flags) {
	_flags = flags;

	if (_flags & Flag::outlineOnly) {
		float minSize = std::min(_width, _height);
		_shape->setOutlineThickness(-minSize*0.1);
		_shape->setOutlineColor(sf::Color(255, 255, 255));
		_shape->setFillColor(sf::Color(0, 0, 0, 0));
	}
}