#pragma once

#include "GameScreen.h"

class MenuScreen : public GameScreen
{
public:
  MenuScreen(sf::RenderWindow* render_window);

  virtual void setup();
private:
	static const int BTN_GAP = 40;
};