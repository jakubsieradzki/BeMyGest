#include "EntityFactory.h"

using sf::Texture;

Player EntityFactory::CreatePlayer(
  Texture* texture,
  float position_x,
  float position_y,
  float scale)
{
  Player player(texture);
  player.setPosition(position_x, position_y);
  player.setOrigin(135.0f, 24.5f);
  player.setScale(scale, scale);
  return player;
}

Seashell* EntityFactory::CreateDynamicSeashell(
  Texture* texture,
  unsigned points,
  float position_on_map_x,
  float scale)
{
  auto seashell = new Seashell(texture);
  seashell->setScore(static_cast<float>(points));
  seashell->SetXPositionOnMap(position_on_map_x);
  seashell->setScale(scale, scale);
  return seashell;
}

Starfish* EntityFactory::CreateDynamicStarfish(
  Texture* texture,
  unsigned points,
  float position_on_map_x,
  float scale)
{
  auto starfish = new Starfish(texture);
  starfish->setScore(points);
  starfish->SetXPositionOnMap(position_on_map_x);
  starfish->setScale(scale, scale);
  return starfish;
}

Enemy* EntityFactory::CreateDynamicEnemy(
  Texture* texture,
  EnemyType type,
  unsigned points,
  float position_on_map_x,
  float scale)
{
  auto enemy = new Enemy(texture);
  //enemy->setType(type);
  enemy->setScore(static_cast<float>(points));
  enemy->SetXPositionOnMap(position_on_map_x);
  enemy->setScale(scale, scale);
  return enemy;
}
