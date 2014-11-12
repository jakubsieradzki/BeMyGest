#include "FreePlayingGame.h"
#include "SimpleMusicBlockFactory.h"
#include "SimpleMusicBlockParser.h"
#include "Flute.h"

#include <iostream>

FreePlayingGame::FreePlayingGame(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{
  setupDependencies();
}

void FreePlayingGame::setupDependencies()
{
	blocks_provider_.setBlockParser(new SimpleMusicBlockParser());
	blocks_provider_.setBlocksFactory(new SimpleMusicBlockFactory());	
}

void FreePlayingGame::setup()
{
	blocks_provider_.createBlocks(level_file_);
	std::vector<AbstractArea*> areas = blocks_provider_.getBlocks();
	for (auto it = areas.begin(); it != areas.end(); it++)
	{
		area_mgr_->addArea((*it));
	}
}

void FreePlayingGame::customUpdate() 
{  
}

void FreePlayingGame::onActivation()
{
  game_clock_.restart();
}