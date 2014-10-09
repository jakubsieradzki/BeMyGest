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
  rect.setFillColor(color_);
	rect.setOutlineColor(sf::Color(0, 0, 0, 255));
  rect.setOutlineThickness(1.0f);
  render_window->draw(rect);
}

bool AbstractArea::isWithinArea(unsigned x, unsigned y)
{
	return 
		x > x_ && x < x_ + width_
		&&
		y > y_ && y < y_ + height_;
}