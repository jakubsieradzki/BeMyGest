#include "MusicBlocksProvider.h"
#include <iostream>

MusicBlocksProvider::MusicBlocksProvider()
{
	update_time_ = 5000.0;
}

MusicBlocksProvider::~MusicBlocksProvider()
{
	for (std::map<float, AbstractArea*>::iterator it = waiting_areas_.begin(); it != waiting_areas_.end(); ++it)
	{
   delete it->second;
	}
	waiting_areas_.clear();

	delete parser_;
	delete block_factory_;
}

void MusicBlocksProvider::initialize()
{	
	std::vector<MusicNote>::iterator it;
	for (it = parser_->getMusicNotes().begin(); it != parser_->getMusicNotes().end(); it++)
	{
		float start_time = (*it).start_time();
		AbstractArea *area = block_factory_->create((*it));
		waiting_areas_.insert(std::pair<float, AbstractArea*>(start_time, area)); 
	}
}

void MusicBlocksProvider::updateAreas(AreaManager *area_manager)
{		
	if (waiting_areas_.empty())
	{
		return;
	}

	float current_time = static_cast<float>(clock_->getElapsedTime().asMilliseconds());
	if (current_time + update_time_ > waiting_areas_.begin()->first)
	{						
		//std::cout << "current time: " << current_time << std::endl;
		//std::cout << "note time: " << waiting_areas_.begin()->first << std::endl;
		area_manager->addArea(waiting_areas_.begin()->second);
		waiting_areas_.erase(waiting_areas_.begin());		
	}
}