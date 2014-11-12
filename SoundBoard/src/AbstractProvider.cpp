#include "AbstractProvider.h"

AbstractProvider::AbstractProvider()
{}

AbstractProvider::~AbstractProvider()
{
	delete block_parser_;
	delete block_factory_;
}

std::vector<AbstractArea*> AbstractProvider::getBlocks()
{
	return blocks_;
}

void AbstractProvider::createBlocks(std::string level_file_)
{	
	std::vector<MusicBlock>::iterator it;
	std::vector<MusicBlock> musicBlocks = block_parser_->parse(level_file_);
	for (it = musicBlocks.begin(); it != musicBlocks.end(); it++)
	{
		AbstractArea* area = block_factory_->create((*it));
		blocks_.push_back(area);
	}
}
