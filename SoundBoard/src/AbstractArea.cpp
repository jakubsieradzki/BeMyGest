#include "AbstractArea.h"

AbstractArea::~AbstractArea()
{

}

void AbstractArea::update(unsigned int x, unsigned int y)
{
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
  sf::RectangleShape rect(sf::Vector2f(width_, height_));
  rect.setPosition(x_, y_);
  rect.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 0.0f));
  rect.setOutlineColor(color_);
  rect.setOutlineThickness(5.0f);
  render_window->draw(rect);
}

bool AbstractArea::isWithinArea(unsigned x, unsigned y)
{
	return 
		x > x_ && x < x_ + width_
		&&
		y > y_ && y < y_ + height_;
}