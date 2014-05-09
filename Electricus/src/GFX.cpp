#include "GFX.h"
#include "Log.h"

using std::string;
using sf::Image;
using sf::Texture;
using sf::Sprite;

namespace GFX {
  
Image LoadImage(string file_path)
{
  Image image;
  if(!image.loadFromFile(file_path))
  {
    Log::error("Can't load (" + file_path + ")");
    if(!image.loadFromFile(TEXTURE_NOT_FOUND))
    {
      Log::fatalError("Can't load default image");
      exit(1);
    }
  }
  else {
    Log::info("Loaded image (" + file_path + ")");
  }
  image.createMaskFromColor(DEFAULT_TRANSPARENCY_MASK);
  return image;
}

Texture LoadTexture(string file_path)
{
  Texture texture;
  if(!texture.loadFromImage(LoadImage(file_path))) {
    Log::error("Can't create texture from image (" + file_path + ")");
  }
  return texture;
}
// ~GFX::
}
