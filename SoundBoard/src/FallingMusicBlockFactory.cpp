#include "FallingMusicBlockFactory.h"
#include <Clarinet.h>
#include <Bowed.h>
#include <PercFlut.h>
#include "ColorMap.h"

AbstractArea* FallingMusicBlockFactory::create(MusicBlock music_block)
{
	sf::CircleShape * rect = new sf::CircleShape(music_block.width());
	//sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(music_block.width(), music_block.height()));
	rect->setPosition(sf::Vector2f(music_block.x(), music_block.y()));	
	rect->setFillColor(ColorMap::map().get(music_block.note()));
	rect->setOutlineColor(sf::Color::Black);
  rect->setOutlineThickness(1.0f);

	builder_
		.withShape(rect)
		.withInstrument(new PercFlut())
		.withFreq(music_block.note())
		.withFinalPosition(music_block.finalPosition())
		.withStartTime(music_block.startTime())
		.withDuration(music_block.duration());

	return builder_.build();
}