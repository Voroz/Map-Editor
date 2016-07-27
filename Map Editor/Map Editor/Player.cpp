#include "Player.h"



Player::Player(Vector2<float> pos, Vector2<float> size, const float mass, const float bouncyness) :
	GameRectObject(1, pos, size, mass, bouncyness)
{
	_shape->setFillColor(sf::Color::Green);
}
Player::Player(float x, float y, float width, float height, const float mass, const float bouncyness) :
	GameRectObject(1, x, y, width, height, mass, bouncyness)
{
	_shape->setFillColor(sf::Color::Green);
}
Player::~Player(){
}

int Player::identify() {
	return 2;
}