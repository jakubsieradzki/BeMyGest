#include "FreePlayingGame.h"
#include "SimpleMusicBlockFactory.h"
#include "SimpleMusicBlockParser.h"
#include "Flute.h"

#include <iostream>

FreePlayingGame::FreePlayingGame(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{
  setup();
}

void FreePlayingGame::setup()
{
	blocks_provider_.setBlockParser(new SimpleMusicBlockParser("resource/musicFiles/test.txt"));
	blocks_provider_.setBlocksFactory(new SimpleMusicBlockFactory());
	blocks_provider_.createBlocks();

	std::vector<AbstractArea*>::iterator it;
	std::vector<AbstractArea*> areas = blocks_provider_.getBlocks();
	for (it = areas.begin(); it != areas.end(); it++)
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