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
	AbstractProvider blocks_provider_;	
	// move to separate class (TextDisplay or smth)
	sf::Font font;
	sf::Text text;

	void setupDependencies();
};