#include "AbstractArea.h"
#include <math.h>

SoundMovingAreav2::SoundMovingAreav2(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq, sf::Vector2f final_position, float start_t, float duration, sf::Vector2f velocity)
	: SoundArea(shape, instrument, baseFreq), final_position_(final_position), velocity_(velocity), start_t_(start_t)
{	
	initial_pos_.x = shape_->getPosition().x;
	initial_pos_.y = shape_->getPosition().y;
	end_t_ = start_t_ + duration;
	sf::Vector2f diff = final_position - shape_->getPosition();
	float length = sqrt(diff.x * diff.x + diff.y * diff.y);

	track_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));		
	track_shape_->setOutlineThickness(0.0);
	float scale_factor = (length + track_shape_->getSize().x) / track_shape_->getSize().x;
	track_shape_->scale(scale_factor, 1.0);	

}

SoundMovingAreav2::~SoundMovingAreav2()
{
}

void SoundMovingAreav2::update(unsigned int x, unsigned int y)
{
	AbstractArea::update(x, y);
	//shape_->move(velocity_.x, velocity_.y);
	if (this->x() >= final_position_.x)
	{
		removable_ = true;
	}
}

void SoundMovingAreav2::draw(sf::RenderWindow* render_window)
{
	render_window->draw(*track_shape_);
	AbstractArea::draw(render_window);
}


