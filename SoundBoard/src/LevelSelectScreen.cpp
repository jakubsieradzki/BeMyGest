#include "LevelSelectScreen.h"
#include "GameScreenMgr.h"
#include <boost/filesystem.hpp>
#include "UiButtonFactory.h"

LevelSelectScreen::LevelSelectScreen(sf::RenderWindow* render_window, std::string level_path, GameScreen *game, GameScreenID game_id)
	: GameScreen(render_window), level_count_(0), level_dir_path_(level_path), actual_game_(game), game_id_(game_id)
{	
	setup();
}

LevelSelectScreen::~LevelSelectScreen()
{
}

void LevelSelectScreen::setup()
{
	GameScreenMgr::instance().Add(game_id_, actual_game_);

	boost::filesystem::path levels_path(level_dir_path_);
	boost::filesystem::directory_iterator end_itr;

	for (boost::filesystem::directory_iterator itr(levels_path); itr != end_itr; ++itr)
	{
		if (is_regular_file(itr->path()))
		{						
			std::string current_file = itr->path().string();
			std::cout << current_file << std::endl;
			addNextLevel(current_file);			
		}
	}
}

void LevelSelectScreen::addNextLevel(std::string file_name)
{
	ButtonConfig config = buttonConfig();
	std::string name = file_name.substr(file_name.find_last_of("\\")+1);

	UiButtonProperties properties(config.position_, config.size_, name.substr(0, name.find_last_of(".")));
	Button *level_btn = UiButtonFactory::instance().createButton(properties, LEVEL_SELECT_BUTTON);
	level_btn->setAction([file_name, this](){    
		auto game = GameScreenMgr::instance().Get(game_id_);
		game->setLevelFile(file_name);
		game->setup();
    GameScreenMgr::instance().SetActive(game_id_);		
  });

	level_count_++;
	area_mgr_->addArea(level_btn);
}

LevelSelectScreen::ButtonConfig LevelSelectScreen::buttonConfig()
{	
	int initial_pos_x = 50;
	int initial_pos_y = 50;
	int width = render_window_->getSize().x - 2*initial_pos_x;
	float button_w = (width / COLUMNS) * 0.7;
	float button_h = button_w;
	float gap_x = (((width / COLUMNS) - button_w) * COLUMNS) / (COLUMNS - 1);
	float gap_y = gap_x * 0.6;

	float button_pos_x = INIT_POS_X + (button_w + gap_x) * (getLevelCount() % COLUMNS);
	float button_pos_y = INIT_POS_Y + (button_h + gap_y) * (getLevelCount() / COLUMNS);
	
	return ButtonConfig(sf::Vector2f(button_pos_x, button_pos_y), sf::Vector2f(button_w, button_h));
}

Button* LevelSelectScreen::createLevelButton(std::string level_file)
{
	float button_w = 0.2f * render_window_->getSize().x;	
	float button_pos_x = 50;
	float button_pos_y = 50;

	UiButtonProperties properties(sf::Vector2f(button_pos_x, button_pos_y), sf::Vector2f(button_w, button_w), level_file);
  Button *level_btn = new Button(sf::Vector2f(button_pos_x, button_pos_y), sf::Vector2f(button_w, button_w));  
  level_btn->setAction([]{
    GameScreenMgr::instance().SetActive(FREE_PLAYING);
  });

	return level_btn;
}

void LevelSelectScreen::customDrawing()
{
}

void LevelSelectScreen::customUpdate()
{
}

void LevelSelectScreen::onActivation()
{
	game_clock_.restart();
}

