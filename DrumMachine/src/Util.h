#pragma once

#include <SFML/Graphics.hpp>
#include <XnCppWrapper.h>
#include <vector>

namespace Util
{
  void ConvertSkeletonMarkersToScreenPoints(
    xn::DepthGenerator& depth_generator, 
    std::vector<XnSkeletonJointPosition>& skeleton_markers, 
    std::vector<sf::Vector2f>* screen_points)
  {
    for (auto it = skeleton_markers.begin(); it != skeleton_markers.end(); ++it)
    {
      XnPoint3D screen_point;
      depth_generator.ConvertRealWorldToProjective(1, &(it->position), &screen_point);
      screen_points->push_back(sf::Vector2f(screen_point.X, screen_point.Y));
    }
  }
}