#ifndef BMG_OPEN_NI_UTIL_H_
#define BMG_OPEN_NI_UTIL_H_

#include <functional>
#include <XnCppWrapper.h>
#include <vector>

namespace bmg {

void OnError(XnStatus status, std::function<void()> func) {
  if (status != XN_STATUS_OK) {
    func();
  }
}

/*
 *  Calculating depth using accumulative histogram
 */
void CalculateDepth(
  const XnDepthPixel* depth_pixels,
  unsigned depth_x_res,
  unsigned depth_y_res,
  unsigned max_depth,
  XnRGB24Pixel* output) {
  
  assert(max_depth > 0);
  std::vector<float> acc_hist(max_depth);
  int num_valid_points = 0;

  for (unsigned i = 0; i < depth_x_res * depth_y_res; ++i) {
    XnDepthPixel pixel = depth_pixels[i];   
    if (pixel != 0 && pixel < max_depth) {
      ++acc_hist[pixel];
      ++num_valid_points;
    }
  }
  for (unsigned i = 1; i < max_depth; ++i) {
    acc_hist[i] += acc_hist[i-1];
  }
  if (num_valid_points > 0) 
  {    
    for (unsigned i = 1; i < max_depth; i++) {
      acc_hist[i] = (float)(256 * (1.0f - (acc_hist[i]/num_valid_points)));
    }
  }
  for (unsigned i = 0; i < depth_x_res * depth_y_res; ++i) {
    output[i].nBlue = output[i].nGreen = output[i].nRed = (unsigned)acc_hist[depth_pixels[i]];
  }
}

// ~~ bmg::
}

#endif