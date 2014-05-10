#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Seashell.h"
#include "Starfish.h"
#include "Enemy.h"

class EntityFactory
{
public:
  static Player CreatePlayer(sf::Texture* texture, float position_x, float position_y, float scale);
  static Seashell* CreateDynamicSeashell(sf::Texture* texture, unsigned points, float position_on_map_x, float scale);
  static Starfish* CreateDynamicStarfish(sf::Texture* texture, unsigned points, float position_on_map_x, float scale);
  static Enemy* CreateDynamicEnemy(sf::Texture* texture, EnemyType type, unsigned points, float position_on_map_x, float scale);

private:
};
