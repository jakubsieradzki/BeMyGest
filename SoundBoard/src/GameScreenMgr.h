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
  
  void SetActive(GameScreenID id) {
    if (game_screens.find(active_screen_id) != game_screens.end()) {
      game_screens[active_screen_id]->onLeave();
    }		
    active_screen_id = id;
    game_screens[active_screen_id]->onActivation();
  }

  GameScreen* GetActive() {
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

private:
  GameScreenMgr() : 
    active_screen_id(MAIN_MENU) {};
  GameScreenMgr(const GameScreenMgr&);
  GameScreenMgr& operator=(const GameScreenMgr&);

  ~GameScreenMgr() {
    for (auto it = game_screens.begin(); it != game_screens.end(); ++it) {
      delete it->second;
    }
    game_screens.clear();
  }
  	
  GameScreenID active_screen_id;	
  std::map<GameScreenID, GameScreen*> game_screens;	
};