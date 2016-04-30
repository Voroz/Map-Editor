#include "MyView.h"



MyView::MyView(const sf::FloatRect& rectangle, const sf::FloatRect& worldRect) : _worldRect(worldRect), sf::View(rectangle){}
MyView::MyView(const sf::Vector2f& center, const sf::Vector2f& size, const sf::FloatRect& worldRect) : _worldRect(worldRect), sf::View(center, size){}
MyView::~MyView(){

}

void MyView::setCenter(float x, float y) {
	if (x > _worldRect.left + _worldRect.width - getSize().x / 2)//on the right side
	{
		x = _worldRect.left + _worldRect.width - getSize().x / 2;
	}
	else if (x < getSize().x / 2)//on the left side
	{
		x = getSize().x / 2;
	}
	if (y > _worldRect.top + _worldRect.height - getSize().y / 2)//on the bottom side
	{
		y = _worldRect.top + _worldRect.height - getSize().y / 2;
	}
	else if (y < getSize().y / 2)//on the top side
	{
		y = getSize().y / 2;
	}
	sf::View::setCenter(x, y);
}
void MyView::setCenter(const sf::Vector2f& center) {
	float x = center.x;
	float y = center.y;
	if (x > _worldRect.left + _worldRect.width - getSize().x / 2)//on the right side
	{
		x = _worldRect.left + _worldRect.width - getSize().x / 2;
	}
	else if (x < getSize().x / 2)//on the left side
	{
		x = getSize().x / 2;
	}
	if (y > _worldRect.top + _worldRect.height - getSize().y / 2)//on the bottom side
	{
		y = _worldRect.top + _worldRect.height - getSize().y / 2;
	}
	else if (y < getSize().y / 2)//on the top side
	{
		y = getSize().y / 2;
	}
	sf::View::setCenter(x, y);
}