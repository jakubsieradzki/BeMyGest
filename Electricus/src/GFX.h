#pragma once

#include <SFML/Graphics.hpp>

namespace GFX
{
  sf::Image LoadImage(std::string file_path);
  sf::Texture LoadTexture(std::string file_path);
}
