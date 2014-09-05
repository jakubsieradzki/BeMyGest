#pragma once

#include <string>
#include <map>
#include "GameScreen.h"
#include "GameScreenID.h"

class GameScreenMgr
{
public:

  void Add(GameScreenID id, GameScreen* game_screen) {
    game_screens.insert(std::make_pair(id, game_screen));
  }

	void Add(std::string dynamic_id, GameScreen* game_screen)
	{
		dynamic_game_screens.insert(std::make_pair(dynamic_id, game_screen));
	}
  
  void SetActive(GameScreenID id) {
    if (game_screens.find(active_screen_id) != game_screens.end()) {
      game_screens[active_screen_id]->onLeave();
    }
		setDynamic(false);
    active_screen_id = id;
    game_screens[active_screen_id]->onActivation();
  }

	void SetActive(std::string screen_id)
	{
		if (dynamic_game_screens.find(screen_id) != dynamic_game_screens.end())
		{
			dynamic_game_screens[screen_id]->onLeave();
		}
		setDynamic(true);
		dynamic_active_screen_id = screen_id;
		dynamic_game_screens[dynamic_active_screen_id]->onActivation();
	}

  GameScreen* GetActive() {
		if (is_dynamic)
		{
			return dynamic_game_screens[dynamic_active_screen_id];
		}
    return game_screens[active_screen_id];
  }

	GameScreen* Get(GameScreenID id)
	{
		return game_screens[id];
	}

  static GameScreenMgr& instance() {
    static GameScreenMgr inst;
    return inst;
  }

	bool isDynamic() { return is_dynamic; }
	void setDynamic(bool dynamic) { is_dynamic = dynamic; }

private:
  GameScreenMgr() : 
    active_screen_id(MAIN_MENU), is_dynamic(false) {};
  GameScreenMgr(const GameScreenMgr&);
  GameScreenMgr& operator=(const GameScreenMgr&);

  ~GameScreenMgr() {
    for (auto it = game_screens.begin(); it != game_screens.end(); ++it) {
      delete it->second;
    }
    game_screens.clear();

		for (auto it = dynamic_game_screens.begin(); it != dynamic_game_screens.end(); ++it)
		{
			delete it->second;
		}
		dynamic_game_screens.clear();
  }
  
	bool is_dynamic;
  GameScreenID active_screen_id;
	std::string dynamic_active_screen_id;
  std::map<GameScreenID, GameScreen*> game_screens;
	std::map<std::string, GameScreen*> dynamic_game_screens;

};