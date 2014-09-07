#include "SimpleMusicBlockParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

SimpleMusicBlockParser::SimpleMusicBlockParser()
{}

SimpleMusicBlockParser::~SimpleMusicBlockParser()
{
}

std::vector<MusicBlock> SimpleMusicBlockParser::parse(std::string file_path)
{
	std::ifstream file_stream(file_path);
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
			std::cout << "ERROR parsing file: " << file_path <<  std::endl;
			break;
		}

		float start_time, duration, final_x, final_y;
		if (!(iss >> start_time >> duration >> final_x >> final_y))
		{
			std::cout << "INFO no data for moving blocks: " << file_path <<  std::endl;			
		}
		MusicBlock block;
		block.setX(x);
		block.setY(y);
		block.setWidth(width);
		block.setHeight(height);
		block.setNote(note);
		block.setStartTime(start_time);
		block.setDuration(duration);
		block.setFinalPosition(sf::Vector2f(final_x, final_y));

		blocks.push_back(block);	
	}		
	return blocks;
}