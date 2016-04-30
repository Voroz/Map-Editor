#include "Mouse.h"

Mouse::Mouse(sf::RenderWindow &window) {
	_window = &window;
	_pos = Vector2<float>(0, 0);
	_left = false;
	_right = false;
	_mouseWheel = 0;
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
int Mouse::mouseWheel() {
	return _mouseWheel;
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
void Mouse::setMouseWheel(int step) {
	_mouseWheel = step;
}