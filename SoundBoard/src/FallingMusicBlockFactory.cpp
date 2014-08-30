#include "FallingMusicBlockFactory.h"
#include "Flute.h"
#include "ColorMap.h"

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

AbstractArea* FallingMusicBlockFactory::create(MusicBlock music_block)
{
	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(music_block.width(), music_block.height()));
	rect->setPosition(sf::Vector2f(music_block.x(), music_block.y()));	
	rect->setFillColor(ColorMap::map().get(music_block.note()));
	rect->setOutlineColor(sf::Color::Black);
  rect->setOutlineThickness(1.0f);

	sf::Vector2f final_postition(music_block.x() + 200, music_block.y());
	float duration = 4.0;
	builder_
		.withShape(rect)
		.withInstrument(new Flute(300.0))
		.withFreq(music_block.note())
		.withFinalPosition(final_postition)
		.withStartTime(3.0)
		.withDuration(duration);

	return builder_.build();
}