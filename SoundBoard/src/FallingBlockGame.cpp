#include "FallingBlocksGame.h"
#include "SimpleFileParser.h"
#include "FallingMusicBlockFactory.h"
#include "SimpleMusicBlockFactory.h"
#include "SimpleMusicBlockParser.h"
#include <cstdlib>
#include "ResourceManager.h"


FallingBlockGame::FallingBlockGame(sf::RenderWindow* render_window)
	: GameScreen(render_window)
{
	setupDependencies();
	//setup();
}

void FallingBlockGame::setup()
{
	blocks_provider_.createBlocks(level_file_);

	area_mgr_->clearAreas();
	std::vector<AbstractArea*>::iterator it;
	std::vector<AbstractArea*> areas = blocks_provider_.getBlocks();
	for (it = areas.begin(); it != areas.end(); it++)
	{
		area_mgr_->addArea((*it));		
	}
}

void FallingBlockGame::setupDependencies()
{
	text.setFont(ResourceManager::instance().getFont("sansation.ttf"));

	blocks_provider_.setBlockParser(new SimpleMusicBlockParser());
	blocks_provider_.setBlocksFactory(new FallingMusicBlockFactory());
}

void FallingBlockGame::customDrawing()
{
	// for debugging
	// Create a text	
	text.setString(std::to_string(static_cast<long long>(game_clock_.getElapsedTime().asMilliseconds())));
	// Draw it
	render_window_->draw(text);

	render_window_->draw(boundry_line_);
}

void FallingBlockGame::customUpdate()
{
	//blocks_provider_.updateAreas(area_mgr_);	
	/*
	std::vector<SoundMovingAreav2*>::iterator it;
	float cur_time = game_clock_.getElapsedTime().asSeconds();	
	for (it = games_areas_.begin(); it != games_areas_.end(); ++it)
	{
		SoundMovingAreav2 *area = (*it);
		cur_time -= area->startTime();
		float current_position = area->x() - area->initialPosition().x;
		float target_position = area->finalPosition().x - area->initialPosition().x;
		float dx = (cur_time * target_position) / area->endTime();
		dx -= current_position;
		area->shape()->move(dx, 0);
	}
	*/
}

void FallingBlockGame::onActivation()
{
	game_clock_.restart();
}