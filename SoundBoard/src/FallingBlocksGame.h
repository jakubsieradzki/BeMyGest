#pragma once

#include "GameScreen.h"
#include "MusicBlocksProvider.h"

class FallingBlockGame : public GameScreen
{
public:
  FallingBlockGame(sf::RenderWindow* render_window);

  virtual void setup();
	virtual void customDrawing();
	virtual void customUpdate();
	virtual void onActivation();

private:
  sf::Clock game_clock_;
	sf::RectangleShape boundry_line_;	
	MusicBlocksProvider blocks_provider_;

	sf::Font font;
	sf::Text text;

	void setupDependencies();
};