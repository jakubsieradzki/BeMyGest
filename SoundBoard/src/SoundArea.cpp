#include "AbstractArea.h"

SoundArea::SoundArea(float x, float y, float width, float height, sf::Color color, Instrmnt *instrument, StkFloat baseFreq)
	: AbstractArea(x, y, width, height, color), baseFreq_(baseFreq)
{
	soundMaker_.setInstrument(instrument);
	soundMaker_.startStream();
}

SoundArea::SoundArea(sf::Shape* shape, Instrmnt *instrument, StkFloat baseFreq) 
	: AbstractArea(shape), baseFreq_(baseFreq)
{
	soundMaker_.setInstrument(instrument);
	soundMaker_.startStream();
}

void SoundArea::onHover(unsigned int x, unsigned int y)
{
	soundMaker_.playNote(baseFreq_, 0.5);
}

void SoundArea::onLeave(unsigned int x, unsigned int y)
{
	soundMaker_.stopNote();
}