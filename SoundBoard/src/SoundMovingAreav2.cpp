#include "AbstractArea.h"
#include <math.h>

const float SoundMovingAreav2::PREPARE_TIME = 2.0;
const float SoundMovingAreav2::INITIAL_SCALE = 5.0;

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
	sf::Color c = shape_->getFillColor();
	track_shape_->setFillColor(sf::Color(c.r, c.g, c.b, 80));
	float scale_factor = (length + track_shape_->getSize().x) / track_shape_->getSize().x;
	track_shape_->scale(scale_factor, 1.0);	

	// countdown outline
	outline_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));
	sf::Vector2f center(outline_shape_->getSize().x/2, outline_shape_->getSize().y/2);
	//outline_shape_->setOrigin(center);
	outline_shape_->setScale(INITIAL_SCALE, INITIAL_SCALE);	
	//outline_shape_->setOrigin(sf::Vector2f(0,0));
	//outline_shape_->setPosition(shape_->getPosition());
	//sf::Vector2f outline_size(outline_shape_->getSize());	
	//outline_shape_->move(0 ,-100);
	outline_shape_->setOutlineColor(shape_->getFillColor());
	outline_shape_->setFillColor(sf::Color::Transparent);

	ready_ = false;

}

SoundMovingAreav2::~SoundMovingAreav2()
{
	delete track_shape_;
	delete outline_shape_;
}

bool closeToZero(float value)
{
	return (abs(1 - abs(value)) < 3);
}

void SoundMovingAreav2::update(unsigned int x, unsigned int y, sf::Clock clock)
{
	AbstractArea::update(x, y, clock);
	updateOutline(clock);
	updateBlock(clock);

	if (clock.getElapsedTime().asSeconds() > (startTime() - PREPARE_TIME))
	{
		ready_ = true;
	}

	sf::Vector2f check = shape()->getPosition() - finalPosition();
	if (closeToZero(check.x) && closeToZero(check.y))
	{
		removable_ = true;
	}
}

void SoundMovingAreav2::updateOutline(sf::Clock clock)
{
	float cur_time = clock.getElapsedTime().asSeconds() - (startTime() - PREPARE_TIME);
	if (cur_time < 0 || outline_shape_->getScale().x <= 1)
	{
		return;
	}
	
	float a = (1 - INITIAL_SCALE) / PREPARE_TIME;
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
	sf::Vector2f current_position = shape()->getPosition() - initialPosition();
	sf::Vector2f target_position = finalPosition() - initialPosition();
	float dx = (cur_time * target_position.x) / (endTime() - startTime());
	float dy = (cur_time * target_position.y) / (endTime() - startTime());
	dx -= current_position.x;
	dy -= current_position.y;
	shape()->move(dx, dy);
}

void SoundMovingAreav2::draw(sf::RenderWindow* render_window)
{
	render_window->draw(*track_shape_);
	if (outline_shape_->getScale().x >= 1)
	{
		render_window->draw(*outline_shape_);
	}
	AbstractArea::draw(render_window);
}


