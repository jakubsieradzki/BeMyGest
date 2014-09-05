#pragma once

#include "MusicBlockParser.h"

class SimpleMusicBlockParser : public MusicBlockParser
{
public:
	SimpleMusicBlockParser();	
	~SimpleMusicBlockParser();
	virtual std::vector<MusicBlock> parse(std::string file_path);
};