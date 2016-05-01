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

	////////////////////////////////////////////////////////////
	/// \brief Resize the view rectangle relatively to its current size
	///
	/// Resizing the view simulates a zoom, as the zone displayed on
	/// screen grows or shrinks.
	/// \a factor is a multiplier:
	/// \li 1 keeps the size unchanged
	/// \li > 1 makes the view bigger (objects appear smaller)
	/// \li < 1 makes the view smaller (objects appear bigger)
	///
	/// \param factor Zoom factor to apply
	///
	/// \see setSize, move, rotate
	///
	////////////////////////////////////////////////////////////
	void zoom(float factor);

private:
	const sf::FloatRect _worldRect;
};