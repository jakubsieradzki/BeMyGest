#pragma once

#include <SFML/Graphics.hpp>

class UiButtonProperties
{
public:
	UiButtonProperties(sf::Vector2f p, sf::Vector2f s, std::string t) : position(p), size(s), text(t) {}
	~UiButtonProperties() {}
	sf::Vector2f position;
	sf::Vector2f size;
	std::string text;
};