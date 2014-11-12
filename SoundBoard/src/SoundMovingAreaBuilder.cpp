#include "SoundMovingAreaBuilder.h"

SoundMovingAreaBuilder::SoundMovingAreaBuilder()
{
	base_freq_ = 0.0;
	final_position_.x = 0.0;
	final_position_.y = 0.0;
	start_time_ = 0.0;
	duration_ = 0.0;
}

SoundMovingAreaBuilder::~SoundMovingAreaBuilder()
{
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withShape(sf::Shape *shape)
{
	shape_ = shape;
	return *this;
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withInstrument(stk::Instrmnt *instrument)
{
	instrument_ = instrument;
	return *this;
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withFreq(stk::StkFloat baseFreq)
{
	base_freq_ = baseFreq;
	return *this;
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withFinalPosition(sf::Vector2f final_pos)
{
	final_position_ = final_pos;
	return *this;
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withStartTime(float startTime)
{
	start_time_ = startTime;
	return *this;
}

SoundMovingAreaBuilder& SoundMovingAreaBuilder::withDuration(float duration)
{
	duration_ = duration;
	return *this;
}

SoundMovingAreav2* SoundMovingAreaBuilder::build()
{
	sf::Vector2f diff = final_position_ - shape_->getPosition();
	float angle = atan2f(diff.y, diff.x);
	angle *= 180 / PI;
	shape_->rotate(angle);

	float duration = 3.0;
	float length = sqrt(diff.x * diff.x + diff.y * diff.y);
	sf::Vector2f velocity(length / duration, 0);

	return new SoundMovingAreav2(shape_, instrument_, base_freq_, final_position_, start_time_, duration_, velocity);
}