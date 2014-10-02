#include "FallingBlocksGame.h"
#include "FallingMusicBlockFactory.h"
#include "SimpleMusicBlockFactory.h"
#include "SimpleMusicBlockParser.h"
#include <cstdlib>
#include "ResourceManager.h"


FallingBlockGame::FallingBlockGame(sf::RenderWindow* render_window)
	: GameScreen(render_window)
{
	setupDependencies();	
}

void FallingBlockGame::setupDependencies()
{
	text.setFont(ResourceManager::instance().getFont("sansation.ttf"));

	blocks_provider_.setBlockParser(new SimpleMusicBlockParser());
	blocks_provider_.setBlocksFactory(new FallingMusicBlockFactory());
}

void FallingBlockGame::setup()
{
	area_mgr_->clearAreas();

	blocks_provider_.createBlocks(level_file_);
	std::vector<AbstractArea*> areas = blocks_provider_.getBlocks();
	for (auto it = areas.begin(); it != areas.end(); it++)
	{
		area_mgr_->addArea((*it));		
	}
}

void FallingBlockGame::customDrawing()
{
	text.setString(std::to_string(static_cast<long long>(game_clock_.getElapsedTime().asMilliseconds())));
	render_window_->draw(text);	
}

void FallingBlockGame::customUpdate()
{
}

void FallingBlockGame::onActivation()
{
	game_clock_.restart();
}