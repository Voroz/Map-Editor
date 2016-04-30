#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class MyView :
	public sf::View
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Construct the view from a rectangle
	///
	/// \param rectangle Rectangle defining the zone to display
	/// \param worldRect Limit view movement to within this rect.
	///
	////////////////////////////////////////////////////////////
	explicit MyView(const sf::FloatRect& rectangle, const sf::FloatRect& worldRect);

	////////////////////////////////////////////////////////////
	/// \brief Construct the view from its center and size
	///
	/// \param center    Center of the zone to display
	/// \param size		 Size of zone to display
	/// \param worldRect Limit view movement to within this rect.
	///
	////////////////////////////////////////////////////////////
	MyView(const sf::Vector2f& center, const sf::Vector2f& size, const sf::FloatRect& worldRect);
	~MyView();

	////////////////////////////////////////////////////////////
	/// \brief Set the center of the view
	///
	/// \param x X coordinate of the new center
	/// \param y Y coordinate of the new center
	///
	/// \see setSize, getCenter
	///
	////////////////////////////////////////////////////////////
	void setCenter(float x, float y);

	////////////////////////////////////////////////////////////
	/// \brief Set the center of the view
	///
	/// \param center New center
	///
	/// \see setSize, getCenter
	///
	////////////////////////////////////////////////////////////
	void setCenter(const sf::Vector2f& center);

private:
	const sf::FloatRect _worldRect;
};