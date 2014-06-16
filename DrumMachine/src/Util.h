#pragma once

#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <XnCppWrapper.h>
#include <vector>

namespace Util
{
  void ConvertSkeletonMarkersToScreenPoints(
    xn::DepthGenerator& depth_generator, 
    std::vector<XnSkeletonJointPosition>& skeleton_markers, 
    std::vector<sf::Vector2f>& screen_points)
  {
    for (auto it = skeleton_markers.begin(); it != skeleton_markers.end(); ++it)
    {
      XnPoint3D screen_point;
      depth_generator.ConvertRealWorldToProjective(1, &(it->position), &screen_point);
      screen_points.push_back(sf::Vector2f(screen_point.X, screen_point.Y));
    }
  }

  void SetScaleToScreenPoints(std::vector<sf::Vector2f>& screen_points, sf::Vector2f& scale)
  {
    for (auto it = screen_points.begin(); it != screen_points.end(); ++it)
    {
      it->x = it->x*scale.x;
      it->y = it->y*scale.y;
    }
  }

  cv::Mat GetThresholdedImage(cv::Mat* image, int hue_min, int hue_max) 
  {
    cv::Mat imageHSV;
    cv::Mat imageThreshed;

    cv::cvtColor(*image, imageHSV, cv::COLOR_RGB2HSV);
    cv::inRange(imageHSV, cv::Scalar(hue_min, 100, 100), cv::Scalar(hue_max, 255, 255), imageThreshed);
    return imageThreshed;
  }

}
