#pragma once

#include "AbstractArea.h"
#include "MusicNote.h"
#include "MusicBlock.h"

class MusicBlockFactory
{
public:
	virtual AbstractArea* create(MusicNote music_note) = 0;
	virtual AbstractArea* create(MusicBlock music_block) = 0;
};