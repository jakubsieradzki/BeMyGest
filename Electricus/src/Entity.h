#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>
#include "GFX.h"

class Entity
{
	public:
		Entity(sf::Texture* texture);
		const sf::Sprite& getSprite() { return *sprite; }
		const sf::CircleShape& getCollisionAura() { return *collisionAura; }

		bool isCollides(Entity* other);
		virtual void setCollisionState(bool isCollides);

		void setCellPosition(int x, int y) { row = x, col = y; }

		void move(float x, float y);
		void setPosition(float x, float y);
		void setScale(float x, float y);
		void setOrigin(float x, float y);
		virtual void refresh();
		virtual void animate(float offset) { move(offset, 0.0f);};
		void setX(float _x);
		
		int row, col;

		sf::Sprite* sprite;
		sf::CircleShape* collisionAura;

		unsigned int xSize, ySize;
		float collisionAuraRadius;
		float x;
		bool remove;
};

#endif