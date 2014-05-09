#ifndef MAP_H_
#define MAP_H_

#include "global.h"
#include "GfxLoader.h"
#include "Entity.h"

class Map
{
	public:    
		Map(std::string file_path, int rows_, int cols_, int topOffset_ = 100);

    Tile** LoadFromFile(std::string file_path);
		void GridOn(bool gridOn) { this -> gridOn = gridOn; }
		void setEntity(Entity* entity, int row, int col);

		sf::Sprite** rowSprites;
		sf::Sprite** colSprites;
		Entity** assets;
		int rows, cols, topOffset;
		float rowSize, colSize;
		bool gridOn;
		int counter;
    Tile** tiles;
    int size;
	private:
		
};

#endif