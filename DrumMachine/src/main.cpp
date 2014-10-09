#include <iostream>
#include <cmath>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MotionDevice.h"
#include "HumanTracker.h"
#include "DrumMachine.h"
#include "Util.h"

const int WINDOW_W = XN_SVGA_X_RES;
const int WINDOW_H = XN_SVGA_Y_RES;
const std::string WINDOW_NAME = "DrumMachine";

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_NAME);
  MotionDevice motion_device;
  HumanTracker drummer(XN_SKEL_PROFILE_LOWER, motion_device.user_generator());
  drummer.RegisterCallbacks();
  DrumMachine drum_machine(4, 50.0f);
  drum_machine.SetDrumSound(0, "resources\\Jazz Kit\\SD09X01.aif");
  drum_machine.SetDrumSound(1, "resources\\Jazz Kit\\HH09X14.aif");
  drum_machine.SetDrumSound(2, "resources\\Jazz Kit\\TTHI09X01.aif");
  drum_machine.SetDrumSound(3, "resources\\Jazz Kit\\TTHI09X04.aif");

  cv::namedWindow("Video");
  cv::namedWindow("Control");

  int iLowH = 0;
  int iHighH = 11;

  int iLowS = 221; 
  int iHighS = 255;

  int iLowV = 74;
  int iHighV = 160;

  //Create trackbars in "Control" window
  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        window.close();
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        sf::Vector2i click_position = sf::Mouse::getPosition(window);
        Util::Display(sf::Vector2f(static_cast<float>(click_position.x), static_cast<float>(click_position.y)), "Click position: ");

        if (drum_machine.InCalibration())
        {
          drum_machine.SetDrumSetPoint(sf::Vector2f(static_cast<float>(click_position.x), static_cast<float>(click_position.y)));
        }
      }
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
    captured_mat = Util::GetThresholdedImage(&captured_mat, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV));
    cv::Moments moments = cv::moments(captured_mat);

    double moment10 = moments.m10;
    double moment01 = moments.m01;
    double area = moments.m00;

    float posX = static_cast<float>(moment10/area);
    float posY = static_cast<float>(moment01/area);
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
    sf::Vector2f drumstick_position(posX * scale_ratio.x, posY * scale_ratio.y);
    drumstick.setPosition(drumstick_position);
    window.draw(drumstick);

    auto drum_set_points = drum_machine.drum_set_points();
    for (unsigned i = 0; i < drum_set_points.size(); ++i)
    {
      sf::CircleShape drum_set_marker(10.0f);
      drum_set_marker.setFillColor(sf::Color::Red);
      drum_set_marker.setPosition(drum_set_points[i]);
      window.draw(drum_set_marker);
    }

    drum_machine.Update(drumstick_position);

    // >>>>
    window.display();

    cv::imshow("Video", captured_mat);
  }
}
