#include "Starfish.h"

Starfish::Starfish(sf::Texture* texture)
  : Entity(texture), scoreRatio(2)
{}

void Starfish::setCollisionState(bool isCollides)
{
  if(isCollides)
  {
    GameMgr::getInstance().playRandomSound();
    GameMgr::getInstance().addScore(score);
    Entity::setCollisionState(true);
    remove = true;
  }
  else
    Entity::setCollisionState(false);
}
