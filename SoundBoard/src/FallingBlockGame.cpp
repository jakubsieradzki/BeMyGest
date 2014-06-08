#include "FallingBlocksGame.h"

FallingBlockGame::FallingBlockGame(sf::RenderWindow* render_window)
	: GameScreen(render_window)
{
	setup();
}

void FallingBlockGame::setup()
{
	boundry_line_.setPosition(10.0, 200.0);
	boundry_line_.setSize(sf::Vector2f(700, 1));
	boundry_line_.setOutlineThickness(0.1);

	MovingArea* area = new MovingArea(sf::Rect<float>(200, -60, 30, 60), 5000.0, boundry_line_.getPosition().y);
	area->setClock(&game_clock_);
	area_mgr_->addArea(area);
}

void FallingBlockGame::customDrawing()
{
	render_window_->draw(boundry_line_);
}

void FallingBlockGame::onActivation()
{
	game_clock_.restart();
}