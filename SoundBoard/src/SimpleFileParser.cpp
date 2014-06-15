#include "SimpleFileParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

void SimpleFileParser::parse()
{
	std::ifstream file_stream(file_path_);
	std::string line;
	float min_freq = 1000.0f;
	float max_freq = 0.0f;
	while(std::getline(file_stream, line))
	{
		// omit comments
		if (line.compare(0, 1, "#") == 0)
		{
			continue;
		}

		std::istringstream iss(line);
		float freq, start_time, duration;
		if (!(iss >> freq >> start_time >> duration))
		{
			std::cout << "ERROR parsing file: " << file_path_ <<  std::endl;
			break;
		}
		notes_.push_back(MusicNote(freq, start_time * 1000, duration * 1000));
		if (freq < min_freq)
		{
			min_freq = freq;
		}
		if (freq > max_freq)
		{
			max_freq = freq;
		}
	}
	config_.setMinFrq(min_freq);
	config_.setMaxFrq(max_freq);
}