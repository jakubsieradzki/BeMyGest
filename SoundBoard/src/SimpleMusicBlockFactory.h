#pragma once
#include "MusicBlockFactory.h"


class	SimpleMusicBlockFactory : public MusicBlockFactory
{
public:
	virtual AbstractArea* create(MusicNote music_note);
	virtual AbstractArea* create(MusicBlock music_block);
};