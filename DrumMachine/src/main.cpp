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

  cv::namedWindow("Video");

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

    // <<<< OpenCV <<<<
    cv::Mat captured_mat(captured_texture.getSize().y, captured_texture.getSize().x, CV_8UC3);
    sf::Image captured_img = captured_texture.copyToImage();
    for (unsigned x = 0; x < captured_texture.getSize().x; ++x) {
      for (unsigned y = 0; y < captured_texture.getSize().y; ++y) {
        captured_mat.at<cv::Vec3b>(y, x)[0] = captured_img.getPixel(x, y).b;
        captured_mat.at<cv::Vec3b>(y, x)[1] = captured_img.getPixel(x, y).g;
        captured_mat.at<cv::Vec3b>(y, x)[2] = captured_img.getPixel(x, y).r;
      }
    }
    captured_mat = Util::GetThresholdedImage(&captured_mat, 110, 140);
    cv::Moments moments = cv::moments(captured_mat);

    double moment10 = moments.m10;
    double moment01 = moments.m01;
    double area = moments.m00;

    float posX = (float)moment10/area;
    float posY = (float)moment01/area;
    // >>>> OpenCV >>>>

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
    sf::CircleShape drumstick(5.0f);
    drumstick.setPosition(posX * scale_ratio.x, posY * scale_ratio.y);
    window.draw(drumstick);

    // >>>>
    window.display();

    cv::imshow("Video", captured_mat);
  }
}
