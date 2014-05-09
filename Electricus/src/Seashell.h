#ifndef SEASHELL_H_
#define SEASHELL_H_

#include "Entity.h"
#include "GameMgr.h"

class Seashell : public Entity
{
	public:
		Seashell(sf::Texture* texture);
		virtual void setCollisionState(bool isCollides);
		void setScore(float _score) { score = _score; }

	private:
		float score;
};

#endif