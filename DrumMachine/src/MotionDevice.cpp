#include "MotionDevice.h"

using sf::Image;
using sf::Sprite;
using sf::Texture;

MotionDevice::MotionDevice(bool capture_image)
  : capture_image_(capture_image)
{
  XnStatus status = motion_context_.Init();
  if (status != XN_STATUS_OK) {
    // couldn't init openi :(
  }
  if (capture_image_) {
    status = image_generator_.Create(motion_context_);
    if (status != XN_STATUS_OK) {
      // couldn't create image generator
    }
  }  
  motion_context_.StartGeneratingAll();
}

Texture MotionDevice::CaptureImage()
{
  if (capture_image_) 
  {
    image_generator_.GetMetaData(image_metadata_);
    unsigned image_width = image_metadata_.XRes();
    unsigned image_height = image_metadata_.YRes();

    Image raw_image;
    raw_image.create(image_width, image_height);

    const XnRGB24Pixel* pixel;
    const XnRGB24Pixel* image_row = image_metadata_.RGB24Data();

    for (int y = 0; y < image_height; ++y) {
      pixel = image_row;

      for (int x = 0; x < image_width; ++x, ++pixel) {
        raw_image.setPixel(x, y, 
          sf::Color(pixel->nRed, pixel->nGreen, pixel->nRed));
      }
      image_row += image_width;
    }
    sf::Texture raw_texture;
    raw_texture.loadFromImage(raw_image);   
    return raw_texture;
  }
  else
  {
    return Texture();
  }
}
