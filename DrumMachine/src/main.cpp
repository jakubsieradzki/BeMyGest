#include <iostream>

#include <SFML/Graphics.hpp>
#include "MotionDevice.h"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const std::string WINDOW_NAME = "DrumMachine";

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_NAME);
  MotionDevice motion_device(true);

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

    window.draw(sf::Sprite(motion_device.CaptureImage()));

    // >>>>
    window.display();
  }
}