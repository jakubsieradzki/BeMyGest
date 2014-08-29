#pragma once

#include "MusicBlockParser.h"

class SimpleMusicBlockParser : public MusicBlockParser
{
public:
	SimpleMusicBlockParser(const char* file_name);
	~SimpleMusicBlockParser();
	virtual std::vector<MusicBlock> parse();
};