#pragma once

#include "GameScreen.h"
#include "GameScreenID.h"
#include "AbstractArea.h"

class LevelSelectScreen : public GameScreen
{
public:
	LevelSelectScreen(sf::RenderWindow* render_window, std::string level_dir, GameScreen *game, GameScreenID game_id);
	~LevelSelectScreen();

	virtual void setup();
	virtual void customDrawing();
	virtual void customUpdate();
	virtual void onActivation();

	void setGame(GameScreen *game, GameScreenID game_id) { actual_game_ = game; game_id_ = game_id;}	
	int getLevelCount() { return level_count_; }
private:
	static const int COLUMNS = 4;
	static const int INIT_POS_X = 50;
	static const int INIT_POS_Y= 200;

	class ButtonConfig
	{
	public:
		ButtonConfig(sf::Vector2f pos, sf::Vector2f size) : position_(pos), size_(size) {} 
		~ButtonConfig() {} 
		sf::Vector2f position_;
		sf::Vector2f size_;
	};

	GameScreen *actual_game_;
	GameScreenID game_id_;
	std::string level_dir_path_;
	int level_count_;

	void addNextLevel(std::string level_path);
	ButtonConfig buttonConfig();
	Button* createLevelButton(std::string level_path);
};