#include "AbstractArea.h"
#include <math.h>

SoundArea::SoundArea(float x, float y, float width, float height, sf::Color color, Instrmnt *instrument, StkFloat baseFreq)
	: AbstractArea(x, y, width, height, color), baseFreq_(baseFreq)
{
	soundMaker_.setInstrument(instrument);
	soundMaker_.startStream();
}

SoundArea::SoundArea(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq) 
	: AbstractArea(shape), baseFreq_(baseFreq), amplitude_(0.5)
{
	soundMaker_.setInstrument(instrument);
	soundMaker_.startStream();
}

void SoundArea::onHover(unsigned int x, unsigned int y, sf::Clock clock)
{
	if (!inside_)
	{				
		enter_time_ = clock.getElapsedTime().asSeconds();
		soundMaker_.playNote(baseFreq_, amplitude_);		
	}
}

void SoundArea::onLeave(unsigned int x, unsigned int y)
{
	soundMaker_.stopNote();
}

void SoundArea::setAmplitude(float amplitude)
{
	amplitude_ = amplitude;
}

void SoundArea::changeAmplitude(float delta)
{
	amplitude_ += delta;
}

float SoundArea::getAmplitude()
{
	return amplitude_;
}

void SoundArea::update(unsigned int x, unsigned int y, sf::Clock clock)
{
	//soundMaker_.playNote(baseFreq_, amplitude_);
	AbstractArea::update(x, y, clock);
}