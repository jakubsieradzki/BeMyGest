#include "AbstractArea.h"

SoundMovingAreav2::SoundMovingAreav2(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq, sf::Vector2f velocity)
	: SoundArea(shape, instrument, baseFreq), velocity_(velocity)
{
}

SoundMovingAreav2::~SoundMovingAreav2()
{
}

void SoundMovingAreav2::update(unsigned int x, unsigned int y)
{
	AbstractArea::update(x, y);
	shape_->move(velocity_.x, velocity_.y);		
}


