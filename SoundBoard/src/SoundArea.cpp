#include "AbstractArea.h"

SoundArea::SoundArea(unsigned x, unsigned y, unsigned width, unsigned height, AreaColor color, Instrmnt *instrument, StkFloat baseFreq)
	: AbstractArea(x, y, width, height, color), baseFreq_(baseFreq)
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