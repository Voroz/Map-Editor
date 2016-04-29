#include "BoundingRect.h"



BoundingRect::BoundingRect(){
	_position = Vector2<float>(0, 0);
	_center = Vector2<float>(0, 0);
	_width = 0;
	_height = 0;
}
BoundingRect::~BoundingRect(){

}

Vector2<float> BoundingRect::pos() {
	return _position;
}
Vector2<float> BoundingRect::center() {
	return _center;
}
float BoundingRect::top() {
	return -_center.y;
}
float BoundingRect::left() {
	return -_center.x;
}
float BoundingRect::bottom() {
	return top() + _height;
}
float BoundingRect::right() {
	return left() + _width;
}
Vector2<float> BoundingRect::topLeft() {
	return Vector2<float>(left(), top());
}
Vector2<float> BoundingRect::topRight() {
	return Vector2<float>(right(), top());
}
Vector2<float> BoundingRect::bottomRight() {
	return Vector2<float>(right(), bottom());
}
Vector2<float> BoundingRect::bottomLeft() {
	return Vector2<float>(left(), bottom());
}
float BoundingRect::width() {
	return _width;
}
float BoundingRect::height() {
	return _height;
}

void BoundingRect::setPos(const Vector2<float> pos) {
	_position = pos;
}
void BoundingRect::setPos(const float x, const float y) {
	_position = Vector2<float>(x, y);
}
void BoundingRect::setCenter(const Vector2<float> center) {
	_center = center;
}
void BoundingRect::setCenter(const float x, const float y) {
	_center = Vector2<float>(x, y);
}
void BoundingRect::setWidth(const float width) {
	_width = width;
}
void BoundingRect::setHeight(const float height) {
	_height = height;
}