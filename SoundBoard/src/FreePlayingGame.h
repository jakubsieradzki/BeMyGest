#pragma once

#include "GameScreen.h"
#include "AbstractProvider.h"

class FreePlayingGame : public GameScreen
{
public:
  FreePlayingGame(sf::RenderWindow* render_window);

  virtual void setup();
  virtual void customUpdate();
  virtual void onActivation();

private:
  sf::Clock game_clock_;
	AbstractProvider blocks_provider_;

	void setupDependencies();
};