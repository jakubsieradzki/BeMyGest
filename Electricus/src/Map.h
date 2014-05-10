#pragma once

#include <tuple>
#include <utility>

#include "global.h"
#include "GFX.h"
#include "Entity.h"

class Map
{
public:
  Map(std::string file_path, int rows_, int cols_, int topOffset_ = 100);

  static std::pair<Tile**, unsigned> LoadFromFile(std::string file_path);  
  void setEntity(Entity* entity, int row, int col);
  
  Entity** assets;
  int rows_num, cols_num, topOffset;
  float grid_element_x, grid_element_y;	
  int counter;
  Tile** tiles;
  int size;
private:
};
