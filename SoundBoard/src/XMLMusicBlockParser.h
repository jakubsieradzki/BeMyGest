#pragma once

#include "MusicBlockParser.h"

class XMLMusicBlockParser : public MusicBlockParser
{
public:
	XMLMusicBlockParser();
	~XMLMusicBlockParser();
	virtual std::vector<MusicBlock> parse(std::string file_path);
};