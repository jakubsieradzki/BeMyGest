#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

class Player : public Entity
{
	public:
		Player(sf::Texture* texture);		
		virtual void refresh() override;
};

#endif