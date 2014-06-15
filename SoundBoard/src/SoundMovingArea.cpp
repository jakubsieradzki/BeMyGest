#include "AbstractArea.h"

SoundMovingArea::SoundMovingArea(sf::Rect<float> rect, float current_time, float time_delay, int position_delta)
	: MovingArea(rect, current_time, time_delay, position_delta)
{
	idle_color_ = sf::Color(0, 166, 232, 200);
	hover_color_ = sf::Color(0, 93, 130, 200);
	color_ = idle_color_;
}

SoundMovingArea::~SoundMovingArea()
{
	soundMaker_.closeStream();
}

void SoundMovingArea::openStream()
{
	soundMaker_.startStream();
}

void SoundMovingArea::onHover(unsigned int x, unsigned int y)
{
	soundMaker_.playNote(baseFreq_, 0.5);
	color_ = hover_color_;
}

void SoundMovingArea::onLeave(unsigned int x, unsigned int y)
{
	soundMaker_.stopNote();
	color_ = idle_color_;
}
