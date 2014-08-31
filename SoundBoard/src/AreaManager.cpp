#include "AreaManager.h"

AreaManager::~AreaManager()
{
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end(); ++it)
	{		
		delete (*it);
	}
	areas_.clear();
}

void AreaManager::draw()
{
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end(); ++it)
	{				
		if ((*it)->ready())
		{
			(*it)->draw(render_window_);		
		}
	}
}

void AreaManager::update(unsigned int x, unsigned int y, sf::Clock clock)
{	
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end();)
	{				
		(*it)->update(x, y, clock);
		if ((*it)->removable())
		{
			// thread-safe remove (?)
			delete (*it);
			it = areas_.erase(it);
		}
		else 
		{
			++it;
		}
	}
}