#include "GameObject.h"

GameObject::GameObject(Vector2<float> pos, Vector2<float> size, const int flags){
	_flags = flags;
}
GameObject::GameObject(float x, float y, float width, float height, const int flags){
	_flags = flags;
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