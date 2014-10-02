#include "MotionDevice.h"

using sf::Image;
using sf::Texture;

MotionDevice::MotionDevice()
{
  XnStatus status = motion_context_.Init();
  PRINT_ON_ERROR(status, "Motion context failed");
  status = image_generator_.Create(motion_context_);
  PRINT_ON_ERROR(status, "Image generator failed");
  XnMapOutputMode outputMode;
  outputMode.nXRes = XN_SVGA_X_RES;
  outputMode.nYRes = XN_SVGA_Y_RES;
  outputMode.nFPS = 30;
  image_generator_.SetMapOutputMode(outputMode);
  status = depth_generator_.Create(motion_context_);
  PRINT_ON_ERROR(status, "Depth generator failed");
  status = user_generator_.Create(motion_context_);
  PRINT_ON_ERROR(status, "User generator failed");

  status = motion_context_.StartGeneratingAll();
  PRINT_ON_ERROR(status, "Generating all failed");
}

Texture MotionDevice::CaptureImage()
{
  image_generator_.GetMetaData(image_metadata_);
  unsigned image_width = image_metadata_.XRes();
  unsigned image_height = image_metadata_.YRes();

  Image raw_image;
  raw_image.create(image_width, image_height);

  const XnRGB24Pixel* pixel;
  const XnRGB24Pixel* image_row = image_metadata_.RGB24Data();

  for (unsigned y = 0; y < image_height; ++y) {
    pixel = image_row;

    for (unsigned x = 0; x < image_width; ++x, ++pixel) {
      raw_image.setPixel(x, y, 
        sf::Color(pixel->nRed, pixel->nGreen, pixel->nBlue));
    }
    image_row += image_width;
  }
  sf::Texture raw_texture;
  raw_texture.loadFromImage(raw_image);
  return raw_texture;
}

void MotionDevice::Update()
{
  XnStatus status = motion_context_.WaitAndUpdateAll();
  PRINT_ON_ERROR(status, "Update all failed");
}
