#pragma once 

#include "MusicBlockFactory.h"
#include "SoundMovingAreaBuilder.h"

class FallingMusicBlockFactory : public MusicBlockFactory
{
private:		
	SoundMovingAreaBuilder builder_;
public:		
	virtual AbstractArea* create(MusicBlock music_block);
};

