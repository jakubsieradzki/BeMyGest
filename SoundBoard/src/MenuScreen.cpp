#include "MenuScreen.h"

#include "GameScreenMgr.h"
#include "SFML\Graphics.hpp"
#include "UiButtonFactory.h"

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
	UiButtonProperties properties(sf::Vector2f(button_pos_x, button_pos_y), sf::Vector2f(button_w, button_h), "FREE");

  Button *free_playing_btn = UiButtonFactory::instance().createButton(properties, MENU_BUTTON);
  free_playing_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FREE_GAME_LEVELS);
  });
  area_mgr_->addArea(free_playing_btn);

	UiButtonProperties move_properties(sf::Vector2f(button_pos_x, button_pos_y + button_h + BTN_GAP), sf::Vector2f(button_w, button_h), "MOVE");
	Button *moving_game_btn = UiButtonFactory::instance().createButton(move_properties, MENU_BUTTON);
  moving_game_btn->setAction([]{    
    GameScreenMgr::instance().SetActive(FALLING_GAME_LEVELS);		
  });
  area_mgr_->addArea(moving_game_btn);
}