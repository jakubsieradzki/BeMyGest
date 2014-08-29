#pragma once

#include "MusicBlockParser.h"

class XMLMusicBlockParser : public MusicBlockParser
{
public:
	XMLMusicBlockParser(const char* file_name);
	~XMLMusicBlockParser();
	virtual std::vector<MusicBlock> parse();
};