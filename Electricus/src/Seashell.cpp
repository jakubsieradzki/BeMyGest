#include "Seashell.h"

Seashell::Seashell(sf::Texture* texture)
	: Entity(texture), score(1.0f)
{

}

void Seashell::setCollisionState(bool isCollides)
{
	if(isCollides && !remove)
	{
		GameMgr::getInstance().playRandomSound();
		GameMgr::getInstance().addScore(score);
		Entity::setCollisionState(true);
		remove = true;
	}
	else
		Entity::setCollisionState(false);
}