#include "MapFile.h"

MapFile::MapFile(std::string fileName)
{
	std::ifstream file(fileName);

	if(!file.is_open())
		Log::error("Can't open file: " + fileName);
	else
	{
		Log::info("File opened: " + fileName);

		std::string line;
		std::vector<Tile*> vec;
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
		tiles = new Tile*[size];

		for(int i = 0; i < size; ++i)
		{
			tiles[i] = vec[i];
		}
	}
}