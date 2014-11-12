#pragma once

#include <vector>
#include "MusicBlock.h"

class MusicBlockParser
{
public:	
	MusicBlockParser() {}
	~MusicBlockParser() {};	
	virtual std::vector<MusicBlock> parse(std::string file_path) = 0;
};