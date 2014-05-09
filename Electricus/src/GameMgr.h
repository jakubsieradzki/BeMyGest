#ifndef GAME_MGR_H_
#define GAME_MGR_H_

#include "global.h"
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <boost/lexical_cast.hpp>

class GameMgr
{
	public:
		// score management
		void addScore(float points);
		void subScore(float points);
		float getScore();
		void setScore(float points);
		void resetScore();
		void setScoreRatio(int ratio);
		void resetScoreRatio();
		int getScoreRatio() { return scoreRatio; }
		void loadSounds();
		void playRandomSound();
		void playFaultSound();
		void setCellSize(float row, float col) { rowCellSize = row;
												  colCellSize = col; }

		inline static GameMgr& getInstance();
		float rowCellSize, colCellSize;
	private:
		sf::Music* sounds[8];
		sf::Music* skucha;
		float score;
		int scoreRatio;

		GameMgr() : score(0.0f), scoreRatio(1) {}
		GameMgr(const GameMgr& game_mgr) {}
		GameMgr& operator=(const GameMgr& game_mgr) {}
};

inline GameMgr& GameMgr::getInstance()
{
	srand((unsigned)time(NULL));
	static GameMgr instance;
	return instance;
}

#endif