#include "FallingMusicBlockFactory.h"
#include "Flute.h"

AbstractArea* FallingMusicBlockFactory::create(MusicNote music_note)
{
	float x_pos = (music_note.frequency() - config_.minFrq()) / (config_.maxFrq() - config_.minFrq()) * (150.0f - 60.0f);
	x_pos += 200.0f;
	//FIX update time is needed
	float current_time = music_note.start_time() - 5000.0;

	SoundMovingArea* area = new SoundMovingArea(sf::Rect<float>(x_pos, 0, 60, music_note.duration()), current_time, music_note.start_time(), falling_boundry_line_);
	area->setInsrument(new Flute(300.0));
	area->setFrequency(music_note.frequency());
	area->setClock(clock_);
	area->openStream();

	return area;
}