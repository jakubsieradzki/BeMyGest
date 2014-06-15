#include "AbstractArea.h"
#include <cmath>

MovingArea::MovingArea(sf::Rect<float> rect, float current_time, float time_target, int position_delta)
		: AbstractArea(rect.left, rect.top, rect.width, rect.height, sf::Color(200, 200, 200)), time_target_(time_target), position_delta_(position_delta)
{
	action_performed = false;		
	float translation = abs(position_delta_ - y_);//  - height_;	
	speed_ = translation / (time_target_ - current_time);
	time_correction_ = - current_time * speed_;	

	// update height so the note can last 
	height_ *= speed_;	
	position_delay_ = height_;
}

MovingArea::MovingArea(sf::Rect<float> rect)
		: AbstractArea(rect.left, rect.top, rect.width, rect.height, sf::Color(200, 200, 200))
{
	action_performed = false;						
}

void MovingArea::draw(sf::RenderWindow* render_window)
{
	AbstractArea::draw(render_window);
	//y_ = speed_ * clock_->getElapsedTime().asMilliseconds() - height_; // + 
	y_ = speed_ * clock_->getElapsedTime().asMilliseconds() + time_correction_ - position_delay_;

	// add small value to remove block with delay
	if (y_ > position_delta_ + 20 && !action_performed)
	{
		action_performed = true;
		removable_ = true;
		color_ = sf::Color(255, 0, 0);
	}
}