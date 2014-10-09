#include "FreePlayingGame.h"
#include "Flute.h"

#include <iostream>

FreePlayingGame::FreePlayingGame(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{
  setup();
}

void FreePlayingGame::setup()
{
  // define sound area
  StkFloat notes[9] = {
    329.63, 349.23, 392.00,
    440.0, 493.88, 523.25,
    587.33, 659.25, 698.46
  };
  int delta = 150;
  for (unsigned int i = 0; i < (sizeof(notes)/sizeof(*notes)); ++i)
  {
    int m = i % 3;
    int n = i / 3;		
    area_mgr_->addArea(new SoundArea(200.0f + (delta*m), 150.0f + (delta*n), 100.0f, 100.0f, sf::Color(0, 0, 255, 125), new Flute(300.0), notes[i]));
  }  
}

void FreePlayingGame::customUpdate() 
{  
  if (game_clock_.getElapsedTime().asSeconds() > 5) {
    exit(0);
  }
}

void FreePlayingGame::onActivation()
{
  game_clock_.restart();
}