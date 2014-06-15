#include "FallingBlocksGame.h"
#include "SimpleFileParser.h"
#include "FallingMusicBlockFactory.h"
#include <cstdlib>

FallingBlockGame::FallingBlockGame(sf::RenderWindow* render_window)
	: GameScreen(render_window)
{
	setup();
}

void FallingBlockGame::setup()
{
	boundry_line_.setPosition(10.0, 150.0);
	boundry_line_.setSize(sf::Vector2f(700, 1));
	boundry_line_.setOutlineThickness(0.1);	

	setupDependencies();
	blocks_provider_.initialize();

	font.loadFromFile("resource/sansation.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
}

void FallingBlockGame::setupDependencies()
{
	// parser
	SimpleFileParser *parser = new SimpleFileParser();
	parser->setMusicFile("resource/musicFiles/got.bmg");
	// FIX ME parse should not be here
	parser->parse();
	blocks_provider_.setParser(parser);

	// blocks factory
	FallingMusicBlockFactory *blocks_factory = new FallingMusicBlockFactory();
	blocks_factory->setClock(&game_clock_);
	blocks_factory->setBoundryLine(boundry_line_.getPosition().y);	
	blocks_factory->setConfig(parser->getConfig());
	blocks_provider_.setBlocksFactory(blocks_factory);

	blocks_provider_.setClock(&game_clock_);
}

void FallingBlockGame::customDrawing()
{
	// for debugging
	// Create a text	
	//text.setString(std::to_string(static_cast<long long>(game_clock_.getElapsedTime().asMilliseconds())));
	// Draw it
	//render_window_->draw(text);

	render_window_->draw(boundry_line_);
}

void FallingBlockGame::customUpdate()
{
	blocks_provider_.updateAreas(area_mgr_);
}

void FallingBlockGame::onActivation()
{
	game_clock_.restart();
}