#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture) 
	: Entity(texture), score(1.0f)
{
}

void Enemy::setCollisionState(bool isCollides)
{
	if(isCollides && !remove)
	{
		GameMgr::getInstance().playFaultSound();
		GameMgr::getInstance().subScore(score);
		Entity::setCollisionState(true);
		remove = true;
	}
	else
		Entity::setCollisionState(false);
}

void Enemy::setType(EnemyType type)
{
	enemyType = type;

	switch (enemyType)
	{
		case PIRANIA:
			left = Entity::col*GameMgr::getInstance().colCellSize;
			right = left + 2*GameMgr::getInstance().colCellSize;
			break;
		case ZDECHLA:
			bottom = Entity::row * GameMgr::getInstance().rowCellSize - 100;
			top = bottom + 3*GameMgr::getInstance().rowCellSize;
			break;
	}
	move_right = true;
	move_up = true;
}

void Enemy::animate(float offset)
{
	int x, y;
	switch(enemyType)
	{
		case PIRANIA:
			x = static_cast<int>(Entity::sprite -> getPosition().x);

			if(x < (left+=offset))
				move_right = true;
			else if(x > (right+=offset))
				move_right = false;

			if(move_right)
				Entity:move(PIRANIA_SPEED+offset, 0.0f);
			else
				Entity::move(-PIRANIA_SPEED+offset, 0.0f);
			break;
		case BECZKA:
			Entity::move(offset, 0.0f);
			break;
		case ZDECHLA:
			y = static_cast<int>(Entity::sprite -> getPosition().y);

			if(y < bottom)
				move_up = true;
			else if(y > top)
				move_up = false;

			if(move_up)
				Entity::move(offset, ZDECHLA_SPEED);
			else 
				Entity::move(offset, -ZDECHLA_SPEED);
			
			break;
	}

}