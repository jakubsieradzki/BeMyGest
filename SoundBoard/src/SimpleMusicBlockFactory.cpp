#include "SimpleMusicBlockFactory.h"
#include "Flute.h"
#include <PercFlut.h>
#include <Wurley.h>
#include "ColorMap.h"

AbstractArea* SimpleMusicBlockFactory::create(MusicBlock block)
{	
	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(block.width(), block.height()));
	rect->setPosition(sf::Vector2f(block.x(), block.y()));
	rect->setOutlineColor(sf::Color(0, 0, 0, 255));
	rect->setFillColor(ColorMap::map().get(block.note()));
  rect->setOutlineThickness(3.0f);

	return new SoundArea(rect, new PercFlut(), block.note());
}