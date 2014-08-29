#pragma once

#include <SFML/Graphics.hpp>

class ColorMap
{
private:
	std::map<float, sf::Color> colors_;
	void init()
	{
		colors_.insert(std::pair<float, sf::Color>(224.2f, sf::Color(0, 0, 0, 255)));
	}
	ColorMap() { init(); }
	ColorMap(const ColorMap&);
  ColorMap& operator=(const ColorMap&);

public:
	sf::Color get(float note) 
	{
		// from http://codingmess.blogspot.com/2009/05/conversion-of-wavelength-in-nanometers.html

		// colour
		float R, G, B;
    if (note >= 380 && note < 440)
		{
      R = -(note - 440.) / (440. - 350.);
      G = 0.0;
      B = 1.0;
		}
    else if (note >= 440 && note < 490)
		{
      R = 0.0;
      G = (note - 440.) / (490. - 440.);
      B = 1.0;
		}
    else if (note >= 490 && note < 510)
		{
      R = 0.0;
      G = 1.0;
      B = -(note - 510.) / (510. - 490.);
		}
		else if (note >= 510 && note < 580)
		{
      R = (note - 510.) / (580. - 510.);
      G = 1.0;
      B = 0.0;
		}
    else if (note >= 580 && note < 645)
		{
      R = 1.0;
      G = -(note - 645.) / (645. - 580.);
      B = 0.0;
		}
    else if (note >= 645 && note <= 780)
		{
      R = 1.0;
      G = 0.0;
      B = 0.0;
		}
    else
		{
			R = 0.0;
      G = 0.0;
      B = 0.0;
		}

    // intensity correction
		float SSS;
    if (note >= 380 && note < 420)
			SSS = 0.3 + 0.7*(note - 350) / (420 - 350);
    else if (note >= 420 && note <= 700)
      SSS = 1.0;
    else if (note > 700 && note <= 780)
      SSS = 0.3 + 0.7*(780 - note) / (780 - 700);
    else
      SSS = 0.0;
    SSS *= 255;

    return sf::Color(int(SSS*R), int(SSS*G), int(SSS*B), 200);		
	}
	static ColorMap& map()
	{
		static ColorMap colorMap;
		return colorMap;
	}
};