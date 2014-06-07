#include "MenuScreen.h"

#include "GameScreenMgr.h"

MenuScreen::MenuScreen(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{
  setup();
}

void MenuScreen::setup()
{
  Button *free_playing_btn = new Button(200, 50, 200, 100, sf::Color(0, 0, 255, 200));  
  free_playing_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FREE_PLAYING);
  });
  area_mgr_->addArea(free_playing_btn);

	Button *falling_blocks_btn = new Button(200, 300, 200, 100, sf::Color(0, 0, 255, 200));  
  falling_blocks_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FALLING_GAME);
  });
  area_mgr_->addArea(falling_blocks_btn);
}