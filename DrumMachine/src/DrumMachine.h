#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>

class DrumMachine
{
public:
  DrumMachine(int drum_set_size, float hit_distance);

  void Update(sf::Vector2f drumstick_position);

  void SetDrumSound(int drum_set_point, std::string audio_file);
  void SetDrumSetPoint(sf::Vector2f drum_set_point);
  std::vector<sf::Vector2f> drum_set_points() { return drum_set_points_; }

  void Recalibrate() { in_calibration_mode_ = true; }
  bool InCalibration() { return in_calibration_mode_; }

private:
  bool in_calibration_mode_;
  int drum_set_size_;
  float hit_distance_;

  std::vector<sf::Vector2f> drum_set_points_;
  std::map<int, sf::Sound*> drum_set_sounds_;
};
