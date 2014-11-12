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
		onHover(x, y, clock);
		inside_ = true;
	}
	else if(inside_)
	{		
		onLeave(x, y);
		inside_ = false;
	}
}

void AbstractArea::draw(sf::RenderWindow* render_window)
{  
  render_window->draw(*shape_);
}

bool AbstractArea::isWithinArea(unsigned x, unsigned y)
{
	return shape_->getGlobalBounds().contains(x, y);
}