#pragma once

#include <SFML/Graphics.hpp>

class ShapeUtils
{
public:
	static void moveOriginToCenter(sf::Shape *shape)
	{
		float angle = shape->getRotation();
		
		sf::RectangleShape *rect = dynamic_cast<sf::RectangleShape*>(shape);
		if (rect != NULL)
		{
			shape->setOrigin(rect->getSize().x/2, rect->getSize().y/2);
		}
	}

	static sf::Vector2f& scaleFromTo(sf::Vector2f from, sf::Vector2f to)
	{
		float scale_x = to.x / from.x;
		float scale_y = to.y / from.y;

		return sf::Vector2f(scale_x, scale_y);
	}
};