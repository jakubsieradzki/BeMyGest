#pragma once

#include <SFML/Graphics.hpp>
#include "GFX.h"

class Entity
{
public:
  Entity(sf::Texture* texture);
  sf::Sprite& sprite() { return sprite_; }
  sf::CircleShape& collisionAura() { return *collisionAura_; }

  bool isCollides(Entity* other);
  virtual void setCollisionState(bool isCollides);

  void setCellPosition(int x, int y) { row_ = x, col_ = y; }

  void move(float x, float y);
  void setPosition(float x, float y);
  void setScale(float x, float y);
  void setOrigin(float x, float y);
  virtual void refresh();
  virtual void animate(float offset) { move(offset, 0.0f);};
  void SetXPositionOnMap(float _x);
  
  int row_, col_;

  sf::Sprite sprite_;
  sf::CircleShape* collisionAura_;

  unsigned int xSize, ySize;
  float collisionAuraRadius;
  float x_position_on_map;
  bool remove;
};
