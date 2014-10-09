#include "Util.h"
#include <cmath>
#include <iostream>

namespace Util {

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

  cv::Mat GetThresholdedImage(cv::Mat* image, cv::Scalar min, cv::Scalar max)
  {
    cv::Mat imageHSV;
    cv::Mat imageThreshed;

    cv::cvtColor(*image, imageHSV, cv::COLOR_BGR2HSV);
    cv::inRange(imageHSV, min, max, imageThreshed);
    return imageThreshed;
  }

  float CalculateDistance(sf::Vector2f start_point, sf::Vector2f end_point)
  {
    return std::sqrt(
      std::pow(start_point.x-end_point.x, 2)
        + std::pow(start_point.y-end_point.y, 2));
  }

  void Display(sf::Vector2f vector, std::string header /*= ""*/)
  {
    std::cout << header << "(" << vector.x << ", " << vector.y << ")" << std::endl;
  }

}