#ifndef ENEMY_H_
#define ENEMY_H_

#include "global.h"
#include "Entity.h"
#include "GameMgr.h"

class Enemy : public Entity
{
	public:
		Enemy(sf::Texture* texture);
		void setCollisionState(bool isCollides);
		void setScore(float points) { score = points; }
		void setType(EnemyType type);
		virtual void animate(float offset);
	private:
		bool move_right;
		bool move_up;
		float score;
		float left, right, top, bottom;
		EnemyType enemyType;
};

#endif