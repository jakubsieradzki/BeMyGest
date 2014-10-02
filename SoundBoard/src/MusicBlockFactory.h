#pragma once

#include "AbstractArea.h"
#include "MusicBlock.h"

class MusicBlockFactory
{
public:	
	virtual AbstractArea* create(MusicBlock music_block) = 0;
};