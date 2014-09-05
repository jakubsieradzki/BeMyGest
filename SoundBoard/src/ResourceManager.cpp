#include "ResourceManager.h"
#include <iostream>

const char* ResourceManager::IMAGE_PATH = "resource/images/";
const char* ResourceManager::FONT_PATH = "resource/fonts/";
const char* ResourceManager::LEVEL_PATH = "resource/musicFiles/";

ResourceManager::ResourceManager()
{
	// load fonts (replace with iteration over folder)
	std::string fonts[] = { "sansation.ttf" };
	for (int i = 0; i < sizeof(fonts) / sizeof(std::string); ++i)
	{
		sf::Font font;
		std::string font_path(FONT_PATH);
		font_path.append(fonts[i]);
		font.loadFromFile(font_path);
		fonts_.insert(std::pair<std::string, sf::Font>(fonts[0], font));
	}
}

sf::Texture& ResourceManager::getImage(std::string image_name)
{
	std::map<std::string, sf::Texture>::iterator it;
	it = images_.find(image_name);
	if (it == images_.end())
	{
		sf::Texture texture;
		std::string path(ResourceManager::IMAGE_PATH);
		path.append(image_name);
		texture.loadFromFile(path);
		images_.insert(std::pair<std::string, sf::Texture>(image_name, texture));
	}
	return images_.at(image_name);
}

sf::Font &ResourceManager::getFont(std::string font_name)
{
	if (fonts_.find(font_name) != fonts_.end())
	{
		return fonts_.at(font_name);
	}
	std::cout << "[ERROR]: no such font: " << font_name << std::endl;
	sf::Font empty_font;
	return empty_font;
}

