#pragma once

#include <SFML/Graphics.hpp>
#include "AbstractArea.h"
#include <vector>

class AreaManager
{
private:
  sf::RenderWindow* render_window_;	
	std::vector<AbstractArea*> areas_;

	bool isWithinArea(AbstractArea *area, unsigned x, unsigned y); 
public:
	AreaManager(sf::RenderWindow* render_window) : render_window_(render_window) {}
	~AreaManager();
	void addArea(AbstractArea * area) { areas_.push_back(area); }
	void draw();
	void update(unsigned int x, unsigned int y, sf::Clock clock);
};