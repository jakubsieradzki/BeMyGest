#include "Player.h"

Player::Player(sf::Texture* texture)
	: Entity(texture)
{
  collisionAuraRadius = 10.0f;
  collisionAura().setRadius(collisionAuraRadius);
}

void Player::refresh()
{
	unsigned int tempxSize = (unsigned int)(xSize * (sprite().getScale().x));
	unsigned int tempySize = (unsigned int)(ySize * (sprite().getScale().y));
	
	collisionAura().setRadius(collisionAuraRadius);
	collisionAura().setPosition(sprite().getPosition().x, sprite().getPosition().y);
}