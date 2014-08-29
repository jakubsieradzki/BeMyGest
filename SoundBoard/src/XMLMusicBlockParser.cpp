#include "XMLMusicBlockParser.h"

XMLMusicBlockParser::XMLMusicBlockParser(const char* file_path)
: MusicBlockParser(file_path)
{}

XMLMusicBlockParser::~XMLMusicBlockParser()
{}

std::vector<MusicBlock> XMLMusicBlockParser::parse()
{
	std::vector<MusicBlock> result;
	// TODO
	return result;
}