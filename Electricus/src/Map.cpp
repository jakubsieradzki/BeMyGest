#include "Map.h"

#include <fstream>

using std::string;
using std::ifstream;
using std::vector;

Map::Map(std::string file_path, int rows_, int cols_, int topOffset_)
	: rows(rows_), cols(cols_), gridOn(false), counter(0), topOffset(topOffset_)
{
	rowSize = SCREEN_HEIGHT/(float)rows;
	colSize = SCREEN_WIDTH/(float)cols;

	sf::Texture* pozioma = Data::GfxLoader::getInstance().loadTexture("resource/pozioma.png");
	sf::Texture* pionowa = Data::GfxLoader::getInstance().loadTexture("resource/pionowa.png");

	rowSprites = new sf::Sprite*[rows];
	colSprites = new sf::Sprite*[cols];
	assets = new Entity*[MAX_ASSETS_NUMBER];
	for(int i = 0; i < MAX_ASSETS_NUMBER; ++i)
		assets[i] = NULL;

	// poziome
	for(unsigned i = 0; i < rows; ++i)
	{
		rowSprites[i] = new sf::Sprite(*pozioma);
		rowSprites[i] -> setPosition(0.0f, i * rowSize + topOffset);
	}

	// pionowa
	for(unsigned j = 0; j < cols; ++j)
	{
		colSprites[j] = new sf::Sprite(*pionowa);
		colSprites[j] -> setPosition(j * colSize, topOffset);
	}
  tiles = LoadFromFile(file_path);
}

void Map::setEntity(Entity* entity, int row, int col)
{
	float rowPos = row * rowSize;
	float colPos = col * colSize;

	entity -> setPosition(colPos, rowPos + topOffset);
	entity -> setCellPosition(row, col);
	assets[counter++] = entity;
}

Tile** Map::LoadFromFile(string file_path)
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
    size = vec.size();
    auto tiles = new Tile*[size];

    for(int i = 0; i < size; ++i)
    {
      tiles[i] = vec[i];
    }
    return tiles;
  }  
  return nullptr;
}