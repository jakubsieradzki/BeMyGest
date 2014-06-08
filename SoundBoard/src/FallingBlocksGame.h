#pragma once

#include "GameScreen.h"

class FallingBlockGame : public GameScreen
{
public:
  FallingBlockGame(sf::RenderWindow* render_window);

  virtual void setup();
	virtual void customDrawing();
	virtual void onActivation();

private:
  sf::Clock game_clock_;
	sf::RectangleShape boundry_line_;

};