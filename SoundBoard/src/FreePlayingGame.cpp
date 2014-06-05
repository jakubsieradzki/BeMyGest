#include "FreePlayingGame.h"
#include "Flute.h"

FreePlayingGame::FreePlayingGame(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{}

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
    area_mgr_->addArea(new SoundArea(200 + (delta*m), 150 + (delta*n), 100, 100, sf::Color(0.0f, 0.0f, 255.0f, 125.0f), new Flute(300.0), notes[i]));
  }
}