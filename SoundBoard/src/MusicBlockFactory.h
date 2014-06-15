#pragma once

#include "AbstractArea.h"
#include "MusicNote.h"

class MusicBlockFactory
{
public:
	virtual AbstractArea* create(MusicNote music_note) = 0;
};