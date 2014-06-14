#include <iostream>

#include <SFML/Graphics.hpp>

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const std::string WINDOW_NAME = "DrumMachine";

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_NAME);

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
    window.display();
  }
}