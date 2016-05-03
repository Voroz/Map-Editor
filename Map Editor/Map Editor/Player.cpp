#include "Player.h"



Player::Player(Vector2<float> pos, Vector2<float> size) : GameRectObject(pos, size){
	_shape->setFillColor(sf::Color::Green);
}
Player::Player(float x, float y, float width, float height) : GameRectObject(x, y, width, height) {
	_shape->setFillColor(sf::Color::Green);
}
Player::~Player(){
}

int Player::identify() {
	return 2;
}