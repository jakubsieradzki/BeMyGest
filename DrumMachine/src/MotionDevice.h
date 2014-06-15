#pragma once

#include <XnCppWrapper.h>
#include <SFML/Graphics.hpp>

class SpriteTexture {
public:
  SpriteTexture();
private:
};

class MotionDevice
{
public:
  MotionDevice(bool capture_image);

  sf::Texture CaptureImage();

  xn::Context motion_context() {
    return motion_context_;
  }
private:
  bool capture_image_;

  xn::Context motion_context_;
  xn::ImageGenerator image_generator_;
  xn::ImageMetaData image_metadata_;
};