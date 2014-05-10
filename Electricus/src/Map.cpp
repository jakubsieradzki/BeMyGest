#include "Map.h"

#include <fstream>
#include "Log.h"

using std::string;
using std::ifstream;
using std::vector;
using std::pair;
using std::make_pair;

Map::Map(std::string file_path, int rows_, int cols_, int topOffset_)
  : rows_num(rows_), cols_num(cols_), counter(0), topOffset(topOffset_)
{
  grid_element_x = SCREEN_HEIGHT/(float)rows_num;
  grid_element_y = SCREEN_WIDTH/(float)cols_num;
  
  auto result = Map::LoadFromFile(file_path);
  tiles = std::get<0>(result);
  size = std::get<1>(result);

  assets = new Entity*[MAX_ASSETS_NUMBER];
  for(int i = 0; i < MAX_ASSETS_NUMBER; ++i)
    assets[i] = NULL;
}

void Map::setEntity(Entity* entity, int row, int col)
{
  float rowPos = row * grid_element_x;
  float colPos = col * grid_element_y;

  entity -> setPosition(colPos, rowPos + topOffset);
  entity -> setCellPosition(row, col);
  assets[counter++] = entity;
}

pair<Tile**, unsigned> Map::LoadFromFile(string file_path)
{
  ifstream file(file_path);

  if(!file.is_open())
    Log::error("Can't open file: " + file_path);
  else
  {
    Log::info("File opened: " + file_path);

    string line;
    vector<Tile*> vec;
    int row = 0;
    while(getline(file, line))
    {
      for(unsigned i = 0; i < line.length(); ++i)
      {
        if(line[i] != DEFAULT_EMPTY_TILE && line[i] != DEFAULT_EMPTY_TILE2)
        {
          Tile* temp = new Tile();
          temp -> sign = line[i];
          temp -> row = row;
          temp -> col = i;
          vec.push_back(temp);
        }
      }
      ++row;
    }
    unsigned size = vec.size();
    auto tiles = new Tile*[size];

    for(int i = 0; i < size; ++i)
    {
      tiles[i] = vec[i];
    }
    return make_pair(tiles, size);
  }
  return make_pair(nullptr, 0);
}
