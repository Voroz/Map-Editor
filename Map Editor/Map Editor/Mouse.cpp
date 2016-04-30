#include "Mouse.h"

Mouse::Mouse(sf::RenderWindow &window) {
	_window = &window;
	_pos = Vector2<float>(0, 0);
	_left = false;
	_right = false;
	_wheel = 0;
	_wheelClick = false;
}
Mouse::~Mouse() {

}

Vector2<float> Mouse::pos() {
	return _pos;
}
Vector2<float> Mouse::worldPos() {
	return Vector2<float>(_window->mapPixelToCoords(sf::Vector2i(_pos.x, _pos.y)).x, _window->mapPixelToCoords(sf::Vector2i(_pos.x, _pos.y)).y);
}
bool Mouse::left() {
	return _left;
}
bool Mouse::right() {
	return _right;
}
int Mouse::wheel() {
	return _wheel;
}
bool Mouse::wheelClick() {
	return _wheelClick;
}
void Mouse::setPos(Vector2<float> pos) {
	_pos = pos;
}
void Mouse::setLeft(bool left) {
	_left = left;
}
void Mouse::setRight(bool right) {
	_right = right;
}
void Mouse::setWheel(int step) {
	_wheel = step;
}
void Mouse::setWheelClick(bool down) {
	_wheelClick = down;
}