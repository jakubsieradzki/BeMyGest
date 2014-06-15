#include "FileParser.h"

FileParser::FileParser()
{}

FileParser::~FileParser()
{}

void FileParser::setMusicFile(const char* file_path)
{
	file_path_ = file_path;
}

std::vector<MusicNote>& FileParser::getMusicNotes()
{
	return notes_;
}

MusicFileConfig FileParser::getConfig()
{
	return config_;
}