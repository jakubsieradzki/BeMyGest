#include "GfxLoader.h"

namespace Data
{
	sf::Image* GfxLoader::loadImage(std::string path)
	{
		sf::Image* image = new sf::Image();

		if(!image->loadFromFile(path))
		{
			Log::error("Can't load (" + path + ")");
			if(!image -> loadFromFile(TEXTURE_NOT_FOUND)) 
			{
				Log::fatalError("Can't load default image");
				return nullptr;
			}
		} 
		else {
			Log::info("Loaded image (" + path + ")");
		}

		if(mask)
		{
			image -> createMaskFromColor(color);
		}

		return image;
	}

	sf::Texture* GfxLoader::loadTexture(std::string path)
	{
		sf::Texture* texture = new sf::Texture();

		if(!texture -> loadFromImage(*Data::GfxLoader::getInstance().loadImage(path)))
		{
			Log::error("Can't create texture from image (" + path + ")");
			return nullptr;
		}
		else
			return texture;
	}

	sf::Sprite* GfxLoader::loadSprite(std::string path)
	{
		return new sf::Sprite(*Data::GfxLoader::getInstance().loadTexture(path));
	}
}