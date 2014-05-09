#ifndef MAP_FILE_H_
#define MAP_FILE_H_

#include <fstream>
#include <vector>
#include "global.h"
#include "Log.h"

class MapFile
{
	public:
		MapFile(std::string fileName);
		Tile** getTiles();

		Tile** tiles;
		int size;
		float rows, cols;

};

#endif