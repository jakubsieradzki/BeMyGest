#include "AbstractArea.h"
#include <math.h>

const float SoundMovingAreav2::PREPARE_TIME = 1.5;
const float SoundMovingAreav2::INITIAL_SCALE = 5.0;

SoundMovingAreav2::SoundMovingAreav2(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq, sf::Vector2f final_position, float start_t, float duration, sf::Vector2f velocity)
	: SoundArea(shape, instrument, baseFreq), final_position_(final_position), velocity_(velocity), start_t_(start_t)
{	
	initial_pos_.x = shape_->getPosition().x;
	initial_pos_.y = shape_->getPosition().y;
	end_t_ = start_t_ + duration;
	sf::Vector2f diff = final_position - shape_->getPosition();
	float length = sqrt(diff.x * diff.x + diff.y * diff.y);
	float angle = atan2f(diff.y, diff.x);

	// track shape
	track_shape_ = new sf::RectangleShape(sf::Vector2f(length, 10));	
	track_shape_->setPosition(shape_->getPosition());
	track_shape_->setRotation(shape_->getRotation());
	track_shape_->setOutlineThickness(0.0);
	sf::Color c = shape_->getFillColor();
	track_shape_->setFillColor(sf::Color(c.r, c.g, c.b, 80));
	//float scale_factor = (length + track_shape_->getSize().x) / track_shape_->getSize().x;
	//track_shape_->scale(scale_factor, 0.2);
	sf::Vector2f generic_size = ShapeUtils::genericSize(shape_);	
	track_shape_->move(cos(angle)*10/2, sin(angle)*10/2);

	// countdown outline
	outline_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));
	sf::Vector2f center(outline_shape_->getSize().x/2, outline_shape_->getSize().y/2);
	outline_shape_->setScale(INITIAL_SCALE, INITIAL_SCALE);	
	outline_shape_->setOutlineColor(shape_->getFillColor());
	outline_shape_->setFillColor(sf::Color::Transparent);

	ready_ = false;
}

SoundMovingAreav2::~SoundMovingAreav2()
{
	delete track_shape_;
	delete outline_shape_;
}

bool SoundMovingAreav2::atFinalPosition()
{
	sf::Vector2f check = shape()->getPosition() - finalPosition();
	sf::Vector2f sign = initialPosition() - finalPosition();
	float sum = check.x * ShapeUtils::signum<>(sign.x) + check.y * ShapeUtils::signum<>(sign.y);
	return sum <= -10;
}

void SoundMovingAreav2::update(unsigned int x, unsigned int y, sf::Clock clock)
{
	float current_time = clock.getElapsedTime().asSeconds();
	if (readyToPlay(current_time))
	{
		SoundArea::update(x, y, clock);
	}
	updateOutline(clock);
	updateBlock(clock);

	if (current_time > (startTime() - PREPARE_TIME))
	{
		ready_ = true;
	}
	
	if (atFinalPosition())
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
	if (!readyToPlay(cur_time))
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

bool SoundMovingAreav2::readyToPlay(float current_time)
{
	return current_time >= startTime();
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


