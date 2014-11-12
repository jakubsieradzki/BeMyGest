#pragma once

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	static const char* FALLING_LEVEL_PATH;
	static const char* FREE_LEVEL_PATH;

	static ResourceManager& instance()
	{
		static ResourceManager mgr;
		return mgr;
	}

	sf::Texture& getImage(std::string image_name);	
	sf::Font& getFont(std::string font_name);

private:
	static const char* IMAGE_PATH;
	static const char* FONT_PATH;

	std::map<std::string, sf::Texture> images_;
	std::map<std::string, sf::Font> fonts_;

	ResourceManager();
	ResourceManager(const ResourceManager&) {}
	ResourceManager& operator=(const ResourceManager&) {}	
};