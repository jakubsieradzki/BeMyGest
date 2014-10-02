#include "DrumMachine.h"

#include "Util.h"

using sf::Vector2f;
using std::string;
using std::make_pair;

DrumMachine::DrumMachine(int drum_set_size, float hit_distance)
  : in_calibration_mode_(true),
    drum_set_size_(drum_set_size),
    hit_distance_(hit_distance)
{

}

void DrumMachine::SetDrumSetPoint(Vector2f drum_set_point)
{
  if (in_calibration_mode_ && drum_set_points_.size() < drum_set_size_)
  {
    drum_set_points_.push_back(drum_set_point);
  }
  else
  {
    in_calibration_mode_ = false;
  }
}

void DrumMachine::SetDrumSound(int drum_set_point, string audio_file)
{
  if (drum_set_point >= 0 && drum_set_point < drum_set_size_)
  {
    auto sound_buffer = new sf::SoundBuffer();
    if (sound_buffer->loadFromFile(audio_file))
    {
      auto sound = new sf::Sound(*sound_buffer);
      drum_set_sounds_.insert(make_pair(drum_set_point, sound));
    }
  }
}

void DrumMachine::Update(sf::Vector2f drumstick_position)
{
  for (unsigned i = 0; i < drum_set_points_.size(); ++i)
  {
    if (Util::CalculateDistance(drumstick_position, drum_set_points_[i]) <= hit_distance_)
    {
      if (drum_set_sounds_.size() > i) 
      {
        if (drum_set_sounds_[i]->getStatus() != sf::Sound::Status::Playing) 
        {
          drum_set_sounds_[i]->setVolume(100);
          drum_set_sounds_[i]->play();
        } else {
          //drum_set_sounds_[i]->stop();
        }
      }
    }
  }
}
