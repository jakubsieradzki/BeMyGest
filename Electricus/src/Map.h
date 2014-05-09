#ifndef MAP_H_
#define MAP_H_

#include "global.h"
#include "GfxLoader.h"
#include "Entity.h"

class Map
{
	public:
		Map(int rows_, int cols_, int topOffset_ = 100);

		void loadAssets(std::string fileName);
		void setTopOffset(int offset);
		void setGrid(bool gridOn) { this -> gridOn = gridOn; }
		void setEntity(Entity* entity, int row, int col);

		sf::Sprite** rowSprites;
		sf::Sprite** colSprites;
		Entity** assets;
		int rows, cols, topOffset;
		float rowSize, colSize;
		bool gridOn;
		int counter;
	private:
		
};

#endif