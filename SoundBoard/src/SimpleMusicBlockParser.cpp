#include "SimpleMusicBlockParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

SimpleMusicBlockParser::SimpleMusicBlockParser(const char* file_path)
	: MusicBlockParser(file_path)
{}

SimpleMusicBlockParser::~SimpleMusicBlockParser()
{
}

std::vector<MusicBlock> SimpleMusicBlockParser::parse()
{
	std::ifstream file_stream(file_path_);
	std::string line;
	std::vector<MusicBlock> blocks;
	while(std::getline(file_stream, line))
	{
		// omit comments
		if (line.compare(0, 1, "#") == 0)
		{
			continue;
		}

		std::istringstream iss(line);
		float x, y, width, height, note;
		if (!(iss >> x >> y >> width >> height >> note))
		{
			std::cout << "ERROR parsing file: " << file_path_ <<  std::endl;
			break;
		}
		MusicBlock block;
		block.setX(x);
		block.setY(y);
		block.setWidth(width);
		block.setHeight(height);
		block.setNote(note);

		blocks.push_back(block);	
	}		
	return blocks;
}