#include "GameObject.h"

GameObject::GameObject(Vector2<float> pos, Vector2<float> size, const int flags){
	_flags = flags;
	_position = pos;
	_width = size.x;
	_height = size.y;
	_center.x = _width / 2;
	_center.y = _height / 2;
}
GameObject::GameObject(float x, float y, float width, float height, const int flags){
	_flags = flags;
	_position = Vector2<float>(x, y);
	_width = width;
	_height = height;
	_center.x = _width / 2;
	_center.y = _height / 2;
}
GameObject::~GameObject() {
	delete _shape;
}
int GameObject::flags() {
	return _flags;
}
sf::Shape* GameObject::shape() {
	return _shape;
}
void GameObject::update() {

	syncShape();
}