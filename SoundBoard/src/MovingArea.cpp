#include "AbstractArea.h"
#include <cmath>

MovingArea::MovingArea(sf::Rect<float> rect, float time_delay, int position_delta)
		: AbstractArea(rect.left, rect.top, rect.width, rect.height, sf::Color(200, 200, 200)), time_delay_(time_delay), position_delta_(position_delta)
{
	action_performed = false;
	update_time_ = 0.01;
	float translation = abs(position_delta_ - x_);
	float time = time_delay_ / update_time_;
	speed_ = translation / time;
}

void MovingArea::onHover(unsigned int x, unsigned int y)
{

}

void MovingArea::onLeave(unsigned int x, unsigned int y)
{

}

void MovingArea::draw(sf::RenderWindow* render_window)
{
	AbstractArea::draw(render_window);
	if (clock_.getElapsedTime().asSeconds() > update_time_)
	{
		y_ += speed_;		
		clock_.restart();
	}

	if (y_ > position_delta_ && !action_performed)
	{
		action_performed = true;
		color_ = sf::Color(255, 0, 0);
	}
}