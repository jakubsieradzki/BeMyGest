#pragma once

#include "MusicNote.h"
#include "MusicFileConfig.h"
#include <vector>

class FileParser
{
protected:
	const char *file_path_;
	std::vector<MusicNote> notes_;
	MusicFileConfig config_;

public:
	FileParser();
	~FileParser();
	void setMusicFile(const char* file_path);
	std::vector<MusicNote>& getMusicNotes();
	MusicFileConfig getConfig();

	virtual void parse() = 0;
};