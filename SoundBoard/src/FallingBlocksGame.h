#pragma once

#include "GameScreen.h"

class FallingBlockGame : public GameScreen
{
public:
  FallingBlockGame(sf::RenderWindow* render_window);

  virtual void setup();   

private:
  sf::Clock game_clock_;
};