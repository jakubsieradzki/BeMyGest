#pragma once 

#include "MusicBlockFactory.h"
#include "MusicFileConfig.h"

class FallingMusicBlockFactory : public MusicBlockFactory
{
private:
	sf::Clock *clock_;
	MusicFileConfig config_;
	float falling_boundry_line_;
public:	
	void setClock(sf::Clock* clock) { clock_ = clock; }
	void setConfig(MusicFileConfig config) { config_ = config; }
	void setBoundryLine(float boundry_line) { falling_boundry_line_ = boundry_line; }

	virtual AbstractArea* create(MusicNote music_note);
	virtual AbstractArea* create(MusicBlock music_block);
};

