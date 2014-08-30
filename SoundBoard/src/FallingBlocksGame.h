#pragma once

#include "GameScreen.h"
#include "AbstractProvider.h"

class FallingBlockGame : public GameScreen
{
public:
  FallingBlockGame(sf::RenderWindow* render_window);

  virtual void setup();
	virtual void customDrawing();
	virtual void customUpdate();
	virtual void onActivation();

private:
  //sf::Clock game_clock_;
	sf::RectangleShape boundry_line_;	
	AbstractProvider blocks_provider_;
	// --- refacor ---
	std::vector<SoundMovingAreav2*> games_areas_;

	sf::Font font;
	sf::Text text;

	void setupDependencies();
};