#ifndef MAP_H_
#define MAP_H_

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