#include "MenuScreen.h"

#include "GameScreenMgr.h"

MenuScreen::MenuScreen(sf::RenderWindow* render_window)
  : GameScreen(render_window)

{
  setup();
}

void MenuScreen::setup()
{
  Button *btn = new Button(200, 50, 200, 100, sf::Color(0.0f, 0.0f, 255.0f, 200.0f));  
  btn->setAction([]{
    GameScreenMgr::instance().SetActive(FREE_PLAYING);
  });
  area_mgr_->addArea(btn);
}