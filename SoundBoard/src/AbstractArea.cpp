#include "AbstractArea.h"

AbstractArea::~AbstractArea()
{
	if (shape_ != NULL)
	{
		delete shape_;
	}
}

void AbstractArea::update(unsigned int x, unsigned int y, sf::Clock clock)
{
	if (!ready_)
	{
		return;
	}

	if (isWithinArea(x, y))
	{
		onHover(x, y);
	}
	else
	{
		onLeave(x, y);
	}
}

void AbstractArea::draw(sf::RenderWindow* render_window)
{  
	/*
  sf::RectangleShape rect(sf::Vector2f(width_, height_));
  rect.setPosition(x_, y_);
  //rect.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 0.0f));
  rect.setFillColor(color_);
	rect.setOutlineColor(sf::Color(0.0f, 0.0f, 0.0f, 255.0f));
  rect.setOutlineThickness(1.0f);
	*/
  render_window->draw(*shape_);
}

bool AbstractArea::isWithinArea(unsigned x, unsigned y)
{
	return shape_->getGlobalBounds().contains(x, y);
}