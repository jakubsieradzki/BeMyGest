#include "AbstractArea.h"

void Button::onHover(unsigned x, unsigned y)
{
	if (!enabled_) { return; }

	if (inside_ == false)
	{
		enterTime_ = clock();
	}
	else
	{
		progress_ = float( clock () - enterTime_ ) /  CLOCKS_PER_SEC;
		if (progress_ > MAX_TIME)
		{
			enabled_ = false;
			action_();
		}
	}
	inside_ = true;
}

void Button::onLeave(unsigned x, unsigned y)
{
	inside_ = false;
}

void Button::draw(sf::RenderWindow *render_window)
{	
  AbstractArea::draw(render_window);
	// don't draw progress if not needed
	if (!enabled_ || !inside_)
	{
		return; 
	}

	float current_width = (progress_ * width_) / MAX_TIME;
  sf::RectangleShape rect(sf::Vector2f(current_width, height_));
  rect.setPosition(x_, y_);
  rect.setFillColor(sf::Color(0.0f, 255.0f, 0.0f, 200.0f));    
  render_window->draw(rect);
}