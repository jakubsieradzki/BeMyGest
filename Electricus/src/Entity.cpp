#include "Entity.h"

Entity::Entity(sf::Texture* texture) 
	: remove(false)
{
	sprite = new sf::Sprite(*texture);
	collisionAura = new sf::CircleShape();
	xSize = sprite -> getTexture()-> getSize().x;
	ySize = sprite -> getTexture() -> getSize().y;
	if(xSize > ySize)
		collisionAuraRadius = (float)xSize/2.0f;
	else 
		collisionAuraRadius = (float)ySize/2.0f;
	collisionAura -> setRadius(collisionAuraRadius);
	collisionAura -> setFillColor(sf::Color::Transparent);
	collisionAura -> setOutlineColor(sf::Color::Green);
	collisionAura -> setOutlineThickness(1.0f);
	collisionAura -> setPosition(sprite -> getPosition().x + xSize/2.0f-collisionAuraRadius, 
							     sprite -> getPosition().y + ySize/2.0f-collisionAuraRadius);
}

void Entity::move(float x, float y)
{
	sprite -> move(x, y);
	collisionAura -> move(x, y);
}

void Entity::setPosition(float x, float y)
{
	sprite -> setPosition(x, y);
	refresh();
}

void Entity::setScale(float x, float y)
{
	sprite -> setScale(x, y);
	refresh();
}

void Entity::setOrigin(float x, float y)
{
	sprite -> setOrigin(x, y);
	refresh();
}

void Entity::setCollisionState(bool isCollides)
{
	if(isCollides)
		collisionAura -> setOutlineColor(sf::Color::Red);
	else
		collisionAura -> setOutlineColor(sf::Color::Green);
}

bool Entity::isCollides(Entity* other)
{
	float xPos = collisionAura -> getPosition().x + collisionAuraRadius;
	float yPos = collisionAura -> getPosition().y + collisionAuraRadius;

	float xOtherPos = other -> collisionAura -> getPosition().x + other -> collisionAuraRadius;
	float yOtherPos = other -> collisionAura -> getPosition().y + other -> collisionAuraRadius;
	
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
	unsigned int tempxSize = (unsigned int)(xSize * (sprite -> getScale().x));
	unsigned int tempySize = (unsigned int)(ySize * (sprite -> getScale().y));
	if(tempxSize > tempySize)
		collisionAuraRadius = tempxSize/2.0f;
	else 
		collisionAuraRadius = tempySize/2.0f;
	collisionAura -> setRadius(collisionAuraRadius);
	collisionAura -> setPosition(sprite -> getPosition().x + (tempxSize)/2.0f-collisionAuraRadius-sprite->getOrigin().x, 
								 sprite -> getPosition().y + (tempySize)/2.0f-collisionAuraRadius - sprite -> getOrigin().y);
}

void Entity::setX(float _x)
{
	x = _x;
}