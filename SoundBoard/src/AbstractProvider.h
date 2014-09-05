#pragma once

#include "AbstractArea.h"
#include "MusicBlockParser.h"
#include "MusicBlockFactory.h"
#include <vector>

class AbstractProvider
{
public:
	AbstractProvider();
	~AbstractProvider();
	std::vector<AbstractArea*> getBlocks();
	void setBlockParser(MusicBlockParser *block_parser) { block_parser_ = block_parser; }
	void setBlocksFactory(MusicBlockFactory *block_factory) { block_factory_ = block_factory; }
	void createBlocks(std::string level_file_);
private:
	MusicBlockParser *block_parser_;
	MusicBlockFactory *block_factory_;
	std::vector<AbstractArea*> blocks_;


};