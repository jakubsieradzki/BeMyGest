#ifndef GFX_LOADER_H_
#define GFX_LOADER_H_

#include <SFML/Graphics.hpp>

#include "global.h"
#include "Log.h"

namespace Data
{
	class GfxLoader
	{
		public:
			sf::Image* loadImage(std::string path);
			sf::Texture* loadTexture(std::string path);
			sf::Sprite* loadSprite(std::string path);
			
			void useMask(bool mask) { this -> mask = mask; }
			void setMask(sf::Color color) { this -> color = color; }
			void setDefaultMask() { mask = true; color = DEFAULT_TRANSPARENCY_MASK; }

			inline static GfxLoader& getInstance();
		private:
			GfxLoader() 
				: mask(true), color(DEFAULT_TRANSPARENCY_MASK) {}
			GfxLoader(const GfxLoader& loader) {}
			GfxLoader& operator=(const GfxLoader& loader) {}

			bool mask;
			sf::Color color;
			static GfxLoader instance;
	};

	inline GfxLoader& GfxLoader::getInstance()
	{
		static GfxLoader instance;
		return instance;
	}

}

#endif