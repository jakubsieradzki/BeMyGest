#pragma once

#include <XnCppWrapper.h>
#include <SFML/Graphics.hpp>

#define PRINT_ON_ERROR(status, error_header) \
  if (status != XN_STATUS_OK) { \
    xnPrintError(status, error_header); \
  }

class MotionDevice
{
public:
  MotionDevice();

  sf::Texture CaptureImage();
  void Update();

  xn::Context& motion_context() {
    return motion_context_;
  }
  xn::UserGenerator& user_generator() { return user_generator_; }
  xn::DepthGenerator& depth_generator() { return depth_generator_; }

private:
  xn::Context motion_context_;
  // image
  xn::ImageGenerator image_generator_;
  xn::ImageMetaData image_metadata_;
  // depth
  xn::DepthGenerator depth_generator_;
  // track
  xn::UserGenerator user_generator_;
};
