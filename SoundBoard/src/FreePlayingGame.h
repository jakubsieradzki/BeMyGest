#pragma once

#include "GameScreen.h"

class FreePlayingGame : public GameScreen
{
public:
  FreePlayingGame(sf::RenderWindow* render_window);

  virtual void setup();
  virtual void customUpdate();
  virtual void onActivation();

private:
  sf::Clock game_clock_;
};