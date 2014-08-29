#pragma once

#include <vector>
#include "MusicBlock.h"

class MusicBlockParser
{
protected:	
	const char* file_path_;
public:
	MusicBlockParser(const char* file_path) { file_path_ = file_path; }
	~MusicBlockParser() {};
	virtual std::vector<MusicBlock> parse() = 0;
};