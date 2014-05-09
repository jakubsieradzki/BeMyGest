#ifndef STARFISH_H_
#define STARFISH_H_

#include "Entity.h"
#include "GameMgr.h"

class Starfish : public Entity
{
	public:
		Starfish(sf::Texture* texture);
		void setCollisionState(bool isCollides);
		void setScoreRatio(int ratio) { scoreRatio = ratio; }
		void setScore(int point) { score = point; }
	private:
		int scoreRatio;
		int score;
};

#endif