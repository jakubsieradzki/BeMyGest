#pragma once

#include "FileParser.h"
#include "MusicBlockFactory.h"
#include "AreaManager.h"

class MusicBlocksProvider
{
public:
	MusicBlocksProvider();
	~MusicBlocksProvider();

	void initialize();
	void setParser(FileParser *parser) { parser_ = parser; }
	void setBlocksFactory(MusicBlockFactory *block_factory) { block_factory_ = block_factory; }
	void setClock(sf::Clock *clock) { clock_ = clock; }

	void updateAreas(AreaManager* area_manager);

private:
	FileParser *parser_;
	MusicBlockFactory *block_factory_;
	std::map<float, AbstractArea*> waiting_areas_;
	sf::Clock *clock_;
	float update_time_;
};