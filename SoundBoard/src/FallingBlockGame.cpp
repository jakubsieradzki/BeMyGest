#include "FallingBlocksGame.h"

FallingBlockGame::FallingBlockGame(sf::RenderWindow* render_window)
	: GameScreen(render_window)
{
	setup();
}

void FallingBlockGame::setup()
{
	MovingArea* area = new MovingArea(sf::Rect<float>(200, 50, 30, 60), 0.5f, 100);
	area->setClock(game_clock_);
	area_mgr_->addArea(area);
}