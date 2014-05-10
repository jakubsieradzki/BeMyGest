#include "Entity.h"

#include <cassert>

Entity::Entity(sf::Texture* texture) 
  : remove(false)
{  
  assert(texture != nullptr);
  sprite_ = sf::Sprite(*texture);  
  collisionAura_ = new sf::CircleShape();
  xSize = sprite_.getTexture()-> getSize().x;
  ySize = sprite_.getTexture() -> getSize().y;
  if(xSize > ySize)
    collisionAuraRadius = (float)xSize/2.0f;
  else 
    collisionAuraRadius = (float)ySize/2.0f;
  collisionAura_ -> setRadius(collisionAuraRadius);
  collisionAura_ -> setFillColor(sf::Color::Transparent);
  collisionAura_ -> setOutlineColor(sf::Color::Green);
  collisionAura_ -> setOutlineThickness(1.0f);
  collisionAura_ -> setPosition(sprite_.getPosition().x + xSize/2.0f-collisionAuraRadius, 
  sprite_.getPosition().y + ySize/2.0f-collisionAuraRadius);
}

void Entity::move(float x, float y)
{
  sprite_.move(x, y);
  collisionAura_ -> move(x, y);
}

void Entity::setPosition(float x, float y)
{
  sprite_.setPosition(x, y);
  refresh();
}

void Entity::setScale(float x, float y)
{
  sprite_.setScale(x, y);
  refresh();
}

void Entity::setOrigin(float x, float y)
{
  sprite_.setOrigin(x, y);
  refresh();
}

void Entity::setCollisionState(bool isCollides)
{
  if(isCollides)
    collisionAura_ -> setOutlineColor(sf::Color::Red);
  else
    collisionAura_ -> setOutlineColor(sf::Color::Green);
}

bool Entity::isCollides(Entity* other)
{
  float xPos = collisionAura_ -> getPosition().x + collisionAuraRadius;
  float yPos = collisionAura_ -> getPosition().y + collisionAuraRadius;

  float xOtherPos = other -> collisionAura_ -> getPosition().x + other -> collisionAuraRadius;
  float yOtherPos = other -> collisionAura_ -> getPosition().y + other -> collisionAuraRadius;
  
  float magnitude = sqrt(pow(abs(xPos - xOtherPos), 2) + pow(abs(yPos - yOtherPos), 2));

  if(magnitude <= collisionAuraRadius + other -> collisionAuraRadius)
  {
    other -> setCollisionState(true);
    setCollisionState(true);
    return true;
  }
  setCollisionState(false);
  other -> setCollisionState(false);
  return false;
}

void Entity::refresh()
{
  unsigned int tempxSize = (unsigned int)(xSize * (sprite_.getScale().x));
  unsigned int tempySize = (unsigned int)(ySize * (sprite_.getScale().y));
  if(tempxSize > tempySize)
    collisionAuraRadius = tempxSize/2.0f;
  else 
    collisionAuraRadius = tempySize/2.0f;
  collisionAura_ -> setRadius(collisionAuraRadius);
  collisionAura_ -> setPosition(sprite_.getPosition().x + (tempxSize)/2.0f-collisionAuraRadius-sprite_.getOrigin().x, 
  sprite_.getPosition().y + (tempySize)/2.0f-collisionAuraRadius - sprite_.getOrigin().y);
}

void Entity::SetXPositionOnMap(float _x)
{
  x_position_on_map = _x;
}