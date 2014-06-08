#include "AbstractArea.h"
#include <cmath>

MovingArea::MovingArea(sf::Rect<float> rect, float time_target, int position_delta)
		: AbstractArea(rect.left, rect.top, rect.width, rect.height, sf::Color(200, 200, 200)), time_target_(time_target), position_delta_(position_delta)
{
	action_performed = false;	
	position_delay_ = height_;
	float translation = abs(position_delta_ - y_);	
	speed_ = translation / time_target_;
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
	y_ = speed_ * clock_->getElapsedTime().asMilliseconds() - position_delay_;

	if (y_ > position_delta_ && !action_performed)
	{
		action_performed = true;
		color_ = sf::Color(255, 0, 0);
	}
}