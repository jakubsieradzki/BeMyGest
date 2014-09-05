#include "MenuScreen.h"

#include "GameScreenMgr.h"
#include "SFML\Graphics.hpp"

MenuScreen::MenuScreen(sf::RenderWindow* render_window)
  : GameScreen(render_window)
{	
  setup();
}

void MenuScreen::setup()
{	
	float button_w = 0.22 * render_window_->getSize().x;
	float button_h = 0.15 * render_window_->getSize().y;
	float button_pos_x = (render_window_->getSize().x - button_w) / 2;
	float button_pos_y = 0.2 * render_window_->getSize().y;

  Button *free_playing_btn = new Button(sf::Vector2f(button_pos_x, button_pos_y), sf::Vector2f(button_w, button_h), "FREE");  
  free_playing_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FREE_PLAYING);
  });
  area_mgr_->addArea(free_playing_btn);

	Button *moving_game_btn = new Button(sf::Vector2f(button_pos_x + button_w + BTN_GAP, button_pos_y), sf::Vector2f(button_w, button_h), "MOVE");
  moving_game_btn->setAction([]{
    //GameScreenMgr::instance().SetActive(FALLING_GAME);
    GameScreenMgr::instance().SetActive(FALLING_GAME_LEVELS);		
  });
  area_mgr_->addArea(moving_game_btn);
	/*
	Button *falling_blocks_btn = new Button(200, 300, 200, 100, sf::Color(0, 0, 255, 200));  
  falling_blocks_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FALLING_GAME);
  });
  area_mgr_->addArea(falling_blocks_btn);
	*/
}