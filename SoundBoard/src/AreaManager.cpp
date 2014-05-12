#include "AreaManager.h"

AreaManager::~AreaManager()
{
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end(); ++it)
	{		
		delete (*it);
	}
}

void AreaManager::draw()
{
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end(); ++it)
	{				
		(*it)->draw(glue_);		
	}
}

void AreaManager::update(unsigned int x, unsigned int y)
{	
	std::vector<AbstractArea*>::iterator it;
	for (it = areas_.begin(); it != areas_.end(); ++it)
	{				
		(*it)->update(x, y);
	}
}