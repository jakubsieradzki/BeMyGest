#include <iostream>

#include <SFML/Graphics.hpp>
#include "MotionDevice.h"
#include "HumanTracker.h"
#include "Util.h"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const std::string WINDOW_NAME = "DrumMachine";

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_NAME);
  MotionDevice motion_device;
  HumanTracker drummer(XN_SKEL_PROFILE_ALL, motion_device.user_generator());
  drummer.RegisterCallbacks();

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    }
    window.clear();
    // <<<<
    motion_device.Update();
    drummer.TrackUsers();

    sf::Texture captured_texture = motion_device.CaptureImage();
    sf::Vector2f scale_ratio(
      WINDOW_W/(float)captured_texture.getSize().x, 
      WINDOW_H/(float)captured_texture.getSize().y);

    sf::Sprite captured_image(captured_texture);
    captured_image.setScale(scale_ratio);
    window.draw(captured_image);

    std::vector<sf::Vector2f> skeleton_screen_points;
    Util::ConvertSkeletonMarkersToScreenPoints(
      motion_device.depth_generator(), 
      drummer.GetHumanAllPartPosition(drummer.GetFirstTrackedHumanId()), 
      skeleton_screen_points);
    Util::SetScaleToScreenPoints(skeleton_screen_points, scale_ratio);

    // draw marker points for whole skeleton
    for (unsigned i = 0; i < skeleton_screen_points.size(); ++i)
    {
      sf::CircleShape skeleton_marker(5.0f);
      skeleton_marker.setPosition(
        skeleton_screen_points[i].x, 
        skeleton_screen_points[i].y);
      window.draw(skeleton_marker);
    }

    // >>>>
    window.display();
  }
}
