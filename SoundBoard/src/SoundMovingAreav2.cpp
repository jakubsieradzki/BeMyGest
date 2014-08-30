#include "AbstractArea.h"
#include <math.h>

const float SoundMovingAreav2::PREPARE_TIME = 1.0;
const float SoundMovingAreav2::INITIAL_SCALE = 4.0;

SoundMovingAreav2::SoundMovingAreav2(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq, sf::Vector2f final_position, float start_t, float duration, sf::Vector2f velocity)
	: SoundArea(shape, instrument, baseFreq), final_position_(final_position), velocity_(velocity), start_t_(start_t)
{	
	initial_pos_.x = shape_->getPosition().x;
	initial_pos_.y = shape_->getPosition().y;
	end_t_ = start_t_ + duration;
	sf::Vector2f diff = final_position - shape_->getPosition();
	float length = sqrt(diff.x * diff.x + diff.y * diff.y);

	// track shape
	track_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));		
	track_shape_->setOutlineThickness(0.0);
	float scale_factor = (length + track_shape_->getSize().x) / track_shape_->getSize().x;
	track_shape_->scale(scale_factor, 1.0);	

	// countdown outline
	outline_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));
	sf::Vector2f center(outline_shape_->getSize().x/2, outline_shape_->getSize().y/2);
	outline_shape_->setOrigin(center);
	outline_shape_->setScale(INITIAL_SCALE, INITIAL_SCALE);	
	sf::Vector2f outline_size(outline_shape_->getSize());	
	outline_shape_->move(outline_size.x/2 ,outline_size.y/2);	
	outline_shape_->setOutlineColor(shape_->getFillColor());
	outline_shape_->setFillColor(sf::Color(0,0,0,0));

}

SoundMovingAreav2::~SoundMovingAreav2()
{
	delete track_shape_;
	delete outline_shape_;
}

void SoundMovingAreav2::update(unsigned int x, unsigned int y, sf::Clock clock)
{
	AbstractArea::update(x, y, clock);
	updateOutline(clock);
	updateBlock(clock);

	if (this->x() >= final_position_.x)
	{
		removable_ = true;
	}
}

void SoundMovingAreav2::updateOutline(sf::Clock clock)
{
	float cur_time = clock.getElapsedTime().asSeconds();
	if (cur_time < (startTime() - PREPARE_TIME) || outline_shape_->getScale().x <= 1)
	{
		return;
	}

	cur_time -= (startTime() - PREPARE_TIME);	
	float a = 1 - INITIAL_SCALE;
	float new_scale = a * cur_time + INITIAL_SCALE;	
	outline_shape_->setScale(new_scale, new_scale);

}

void SoundMovingAreav2::updateBlock(sf::Clock clock)
{
	float cur_time = clock.getElapsedTime().asSeconds();
	if (cur_time < startTime())
	{
		return;
	}
	cur_time -= startTime();
	float current_position = this->x() - initialPosition().x;
	float target_position = finalPosition().x - initialPosition().x;
	float dx = (cur_time * target_position) / (endTime() - startTime());
	dx -= current_position;
	shape()->move(dx, 0);
}

void SoundMovingAreav2::draw(sf::RenderWindow* render_window)
{
	render_window->draw(*track_shape_);
	if (outline_shape_->getScale().x > 1)
	{
		render_window->draw(*outline_shape_);
	}
	AbstractArea::draw(render_window);
}


