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
    std::vector<sf::Vector2f>& screen_points);

  void SetScaleToScreenPoints(std::vector<sf::Vector2f>& screen_points, sf::Vector2f& scale);

  cv::Mat GetThresholdedImage(cv::Mat* image, cv::Scalar min, cv::Scalar max);

  float CalculateDistance(sf::Vector2f start_point, sf::Vector2f end_point);

  void Display(sf::Vector2f vector, std::string header = "");

}
